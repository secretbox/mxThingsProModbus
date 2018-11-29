#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include <mxidaf/Modbus.h>

void
    print_value(
        value_t value,
        value_type_t value_type)
{
    switch(value_type)
    {
    case TAG_VALUE_TYPE_INT:
        printf("Value_i: %" PRId64 "\n", value.i);
        break;
    case TAG_VALUE_TYPE_UINT:
        printf("Value_u: %" PRIu64 "\n", value.u);
        break;
    case TAG_VALUE_TYPE_DOUBLE:
        printf("Value_d: %lf\n", value.d);
        break;
    case TAG_VALUE_TYPE_STRING:
        printf("Value_s: %s\n", value.s);
        free(value.s);
        break;
    default:
        printf("Error: unexpected value_type_t\n");
        break;
    }
}

int
    main(
        int argc,
        const char *argv[])
{
    int rc = 0;

    mxmodbus *modbus_ = mxmodbus_new();
    if (modbus_ == NULL)
    {
        printf("Create mxmodbus object FAIL\n");
        return -1;
    }

    value_t value;
    value_type_t value_type;
    rc = mxmodbus_read(
        modbus_,
        "HAHA",
        "Relay0",
        1000,
        &value,
        &value_type
    );

    if (rc == 0)
    print_value(value, value_type);
    printf("comm argv1->%d",argv[1]);
	value.i = atoi(argv[1]);
    
	value_type=
	mxmodbus_write(
        modbus_,
        "HAHA",
        "Relay0_w",
        1000,
        value,
        value_type
    );

    mxmodbus_delete(modbus_);

    return 0;
}
