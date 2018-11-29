#include <stdio.h>

#include <mxidaf/TagV2.h>

int
    main(
        int argc,
        const char *argv[])
{
    tag *tag_ = tag_new();

    value_t volt;
    volt.d = 1.414;

    tag_publish(
        tag_,
        "electrical-probe",
        "voltage",
        &volt,
        TAG_VALUE_TYPE_DOUBLE,
        "",
        "2016-09-20T11:11:40Z");

    tag_delete(tag_);

    return 0;
}
