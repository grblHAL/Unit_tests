#include "multipart_host.h"
static upload_capture_t *capture(multipartparser *parser)
{
    CHECK(parser->data);
    return parser->data;
}
static upload_part_t *part(multipartparser *parser)
{
    upload_capture_t *upload = capture(parser);
    CHECK(upload->count > 0 && upload->count <= 2);
    return &upload->parts[upload->count - 1];
}
static int body_begin(multipartparser *parser)
{
    upload_capture_t *upload = capture(parser);
    CHECK(!upload->begins && !upload->count);
    upload->begins++;
    return 0;
}
static int part_begin(multipartparser *parser)
{
    upload_capture_t *upload = capture(parser);
    CHECK(upload->begins == 1 && !upload->ends && upload->count < 2);
    if (upload->count)
        CHECK(part(parser)->ended);
    upload->count++;
    return 0;
}
static int field(multipartparser *parser, const char *bytes, size_t length)
{
    upload_part_t *p = part(parser);
    CHECK(!p->headers_done && p->field_length + length < sizeof(p->fields));
    memcpy(p->fields + p->field_length, bytes, length);
    p->field_length += length;
    return 0;
}
static int value(multipartparser *parser, const char *bytes, size_t length)
{
    upload_part_t *p = part(parser);
    CHECK(!p->headers_done && p->value_length + length < sizeof(p->values));
    memcpy(p->values + p->value_length, bytes, length);
    p->value_length += length;
    return 0;
}
static int headers_complete(multipartparser *parser)
{
    upload_part_t *p = part(parser);
    CHECK(!p->headers_done && !p->ended);
    p->headers_done = true;
    return 0;
}
static int data(multipartparser *parser, const char *bytes, size_t length)
{
    upload_part_t *p = part(parser);
    CHECK(p->headers_done && !p->ended && p->length + length <= sizeof(p->bytes));
    memcpy(p->bytes + p->length, bytes, length);
    p->length += length;
    return 0;
}
static int part_end(multipartparser *parser)
{
    upload_part_t *p = part(parser);
    CHECK(p->headers_done && !p->ended);
    p->ended = true;
    return 0;
}
static int body_end(multipartparser *parser)
{
    upload_capture_t *upload = capture(parser);
    CHECK(!upload->ends && part(parser)->ended);
    upload->ends++;
    return 0;
}
void upload_init(upload_capture_t *upload)
{
    memset(upload, 0, sizeof(*upload));
    multipartparser_init(&upload->parser, "grbl-upload");
    upload->parser.data = upload;
    multipartparser_callbacks_init(&upload->callbacks);
    upload->callbacks = (multipartparser_callbacks){
        body_begin, part_begin, field, value, headers_complete, data, part_end, body_end};
}
void upload_feed(upload_capture_t *upload, const char *bytes, size_t length, size_t chunk)
{
    CHECK(chunk > 0);
    for (size_t offset = 0; offset < length;)
    {
        size_t count = length - offset < chunk ? length - offset : chunk;
        CHECK(multipartparser_execute(&upload->parser, &upload->callbacks, bytes + offset, count) ==
              count);
        offset += count;
    }
}
void upload_complete(upload_capture_t *upload, unsigned parts)
{
    CHECK(upload->begins == 1 && upload->ends == 1 && upload->count == parts);
    for (unsigned i = 0; i < parts; i++)
        CHECK(upload->parts[i].headers_done && upload->parts[i].ended);
}
