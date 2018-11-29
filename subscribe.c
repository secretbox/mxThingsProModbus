#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <mxidaf/TagV2.h>

void
    on_tag_callback(
        tag *self,
        const char *equipment_name,
        const char *tag_name,
        value_t *value,
        value_type_t value_type,
        const char *at,
        const char *unit)
{
    printf("Equ: %s, ", equipment_name);
    printf("Tag: %s, ", tag_name);
    printf("Value: ");
    if (value_type == TAG_VALUE_TYPE_INT)
        printf("%" PRId64 ", ", value->i);
    else if (value_type == TAG_VALUE_TYPE_UINT)
        printf("%" PRIu64 ", ", value->u);
    else if (value_type == TAG_VALUE_TYPE_DOUBLE)
        printf("%lf, ", value->d);
    else if (value_type == TAG_VALUE_TYPE_STRING)
    {
        printf("%s, ", value->s);
        free(value->s);
    }
    else if (value_type == TAG_VALUE_TYPE_BYTEARRAY)
    {
        size_t i;
        for(i = 0; i < value->l; i++)
        {
            printf("%02x", value->b[i]);
        }
        printf(", ");
        free(value->b);
    }
    else
        printf(", ");
    printf("Time: %s, ", at);
    printf("Unit: %s\n", unit);
    free(value);
}

int
    main(
        int argc,
        const char *argv[])
{
    tag *tag_ = tag_new();

    tag_subscribe_callback(tag_, on_tag_callback);

    tag_subscribe(
        tag_,
        "electrical-probe",
        "voltage");
    tag_subscribe(
        tag_,
        "electrical-probe",
        "current");

    tag_unsubscribe(
        tag_,
        "electrical-probe",
        "current");

    for(;;)
    {
        sleep(1);
    }

    tag_delete(tag_);

    return 0;
}
