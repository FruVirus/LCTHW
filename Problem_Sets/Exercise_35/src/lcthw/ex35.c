#include <stdio.h>

typedef enum
{
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_STRING,
} VariantType;

struct Variant
{
    VariantType type;

    union
    {
        int as_integer;
        float as_float;
        double as_double;
        char *as_string;
    } data;
};

typedef struct Variant Variant;

void Variant_print(Variant *var)
{
    switch (var->type)
    {
        case TYPE_INT:
            printf("INT: %d\n",var->data.as_integer);
            break;
        case TYPE_FLOAT:
            printf("FLOAT: %f\n",var->data.as_float);
            break;
        case TYPE_DOUBLE:
            printf("DOUBLE: %f\n",var->data.as_double);
            break;
        case TYPE_STRING:
            printf("STRING: %s\n",var->data.as_string);
            break;
        default:
            printf("UNKNOWN TYPE: %d\n",var->type);
    }
}

int main (int argc,char *argv[])
{
    Variant a_int = {a_int.type = TYPE_INT,a_int.data.as_integer = 100};
    Variant a_float = {a_float.type = TYPE_FLOAT,a_float.data.as_float = 100.34};
    Variant a_double = {a_double.type = TYPE_DOUBLE,a_double.data.as_double = 100.3456546465321};
    Variant a_string = {a_string.type = TYPE_STRING,a_string.data.as_string = "YO DUDE!"};

    Variant_print(&a_int);
    Variant_print(&a_float);
    Variant_print(&a_double);
    Variant_print(&a_string);

    // Here's how you access them.
    a_int.data.as_integer = 200;
    a_float.data.as_float = 2.345;
    a_double.data.as_double = 156465.6465451321545;
    a_string.data.as_string = "Hi there.";

    Variant_print(&a_int);
    Variant_print(&a_float);
    Variant_print(&a_double);
    Variant_print(&a_string);
   
    return 0;
}
