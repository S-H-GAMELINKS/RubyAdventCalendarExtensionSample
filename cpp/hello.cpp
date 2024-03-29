#include <ruby.h>
#include <iostream>

class Hello {
    public:
        Hello() {};
        ~Hello() {};
        void say() { std::cout << "Hello Ruby Extension!" << std::endl; };
};

struct WrapHello {
    Hello* hello;
};

static Hello* get_hello(VALUE self) {
    WrapHello *ptr;
    Data_Get_Struct(self, WrapHello, ptr);
    return ptr->hello;
}

static void wrap_hello_free(WrapHello *ptr) {
    delete ptr->hello;
    ruby_xfree(ptr);
}

static VALUE wrap_hello_alloc(VALUE klass) {
    auto *ptr = RB_ALLOC(WrapHello);
    ptr->hello = new(Hello);
    return Data_Wrap_Struct(klass, NULL, wrap_hello_free, ptr);
}

static VALUE wrap_hello_init(VALUE self) {
    return Qnil;
}

static VALUE wrap_hello_say(VALUE self) {
    get_hello(self)->say();
    return Qnil;
}

extern "C" {
    void Init_hello() {
        VALUE rb_cHello = rb_define_class("Hello", rb_cObject);

        rb_define_alloc_func(rb_cHello, wrap_hello_alloc);
        rb_define_private_method(rb_cHello, "initialize", RUBY_METHOD_FUNC(wrap_hello_init), 0);
        rb_define_method(rb_cHello, "say", RUBY_METHOD_FUNC(wrap_hello_say), 0);
    }
}