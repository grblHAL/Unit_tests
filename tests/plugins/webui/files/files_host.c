#include "files_host.h"
#include "networking/http_upload.h"
#include <stdio.h>
bool files_maintenance;
static http_request_t *active_request;
static files_request_t *active_parameters;
static void reset(void) {}
static files_request_t *parameters(http_request_t *request)
{
    CHECK(request && request == active_request && active_parameters);
    return active_parameters;
}
bool webui_maintenance_mode(void) { return files_maintenance; }
char *http_get_param_value(http_request_t *request, const char *key, char *value, uint32_t size)
{
    files_request_t *p = parameters(request);
    const char *text = NULL;
    if (!strcmp(key, "path"))
        text = p->path;
    else if (!strcmp(key, "filename"))
        text = p->filename;
    else if (!strcmp(key, "action"))
        text = p->action;
    else if (!strcmp(key, "quiet"))
        text = p->quiet;
    else
        CHECK(false);
    CHECK(!text || strlen(text) < size);
    strcpy(value, text ? text : "");
    return text ? value : NULL;
}
const char *http_get_uri(http_request_t *request) { return parameters(request)->uri; }
int http_get_header_value_len(http_request_t *request, const char *name)
{
    CHECK(!strcmp(name, "Content-Type"));
    const char *text = parameters(request)->content_type;
    return text ? (int)strlen(text) : -1;
}
char *http_get_header_value(http_request_t *request, const char *name, char *value, uint32_t size)
{
    CHECK(!strcmp(name, "Content-Type"));
    const char *text = parameters(request)->content_type;
    CHECK(text && strlen(text) == size && size < 200);
    memcpy(value, text, size);
    value[size] = 0;
    return value;
}
bool http_set_rom_response_header(http_request_t *request, const char *header)
{
    CHECK(!strcmp(header, "Cache-Control: no-cache\r\n"));
    parameters(request)->headers++;
    return true;
}
void http_set_response_status(http_request_t *request, const char *status)
{
    CHECK(strlen(status) < sizeof(parameters(request)->status));
    strcpy(parameters(request)->status, status);
}
void httpd_free_pbuf(http_request_t *request, struct pbuf *p)
{
    CHECK(p);
    parameters(request)->released++;
}
void files_prepare(http_request_t *request, files_request_t *p)
{
    hal.driver_reset = reset;
    fatfs_prepare();
    CHECK(fs_ram_mount());
    memset(request, 0, sizeof(*request));
    active_request = request;
    active_parameters = p;
}
const char *files_action(http_request_t *request)
{
    vfs_drive_t *drive = fs_get_root_drive();
    CHECK(drive && !strcmp(drive->path, "/"));
    const char *response = fs_action_handler(request, drive);
    CHECK(response && !strcmp(response, "/ram/qry.json"));
    return response;
}
void files_response(char *buffer, size_t capacity)
{
    vfs_file_t *file = vfs_open("/ram/qry.json", "r");
    CHECK(file && file->size < capacity);
    size_t length = vfs_read(buffer, 1, capacity - 1, file);
    CHECK(length == file->size);
    buffer[length] = 0;
    printf("JSON response: %s\n", buffer);
    vfs_close(file);
}
void files_readback(const char *path, const void *expected, size_t size)
{
    char data[128];
    CHECK(size < sizeof(data));
    vfs_file_t *file = vfs_open(path, "r");
    CHECK(file && file->size == size);
    CHECK(vfs_read(data, 1, sizeof(data), file) == size && !memcmp(data, expected, size));
    vfs_close(file);
}
void files_upload(http_request_t *request, const char *name, const void *bytes, size_t size,
                  size_t chunk)
{
    files_request_t *p = parameters(request);
    p->content_type = "multipart/form-data; boundary=grbl-webui";
    CHECK(fs_upload_handler(request, fs_get_sd_drive()) == NULL);
    CHECK(request->post_receive_data && request->post_finished && request->private_data);
    char body[1024];
    int length = snprintf(
        body, sizeof(body),
        "--grbl-webui\r\nContent-Disposition: form-data; name=\"file\"; filename=\"%s\"\r\n"
        "Content-Type: application/octet-stream\r\n\r\n",
        name);
    const char end[] = "\r\n--grbl-webui--\r\n";
    CHECK(length > 0 && size + length + sizeof(end) < sizeof(body) && chunk);
    memcpy(body + length, bytes, size);
    length += size;
    memcpy(body + length, end, sizeof(end) - 1);
    length += sizeof(end) - 1;
    unsigned deliveries = 0;
    for (size_t offset = 0; offset < (size_t)length;)
    {
        size_t count = (size_t)length - offset;
        if (count > chunk)
            count = chunk;
        size_t first = count > 1 ? count / 2 : count;
        struct pbuf tail = {
            .payload = body + offset + first, .len = count - first, .tot_len = count - first};
        struct pbuf head = {.payload = body + offset,
                            .len = first,
                            .tot_len = count,
                            .next = count > first ? &tail : NULL};
        CHECK(request->post_receive_data(request, &head) == ERR_OK);
        offset += count;
        deliveries++;
    }
    file_upload_t *upload = request->private_data;
    CHECK(upload->state == Upload_Complete && upload->uploaded == size && !upload->file.handle);
    char response_uri[128] = "";
    request->post_finished(request, response_uri, sizeof(response_uri));
    CHECK(!strcmp(response_uri, "/ram/qry.json") && p->released == deliveries);
    CHECK(!request->private_data && !request->on_request_completed && !p->status[0]);
}
