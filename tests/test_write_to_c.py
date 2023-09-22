import myproj._example


def test_write_to_c_member():
    a = myproj._example.TestBind()

    test_value = 5
    # write to the C++ member by Python binding function.
    a.a_factor = test_value
    # get back the value by C++ function (with additional Python 
    # binding to pass the value returned by the C++ function).
    assert a.get_a() == test_value


def test_enclosed_class():
    a = myproj._example.TestBind()
    b = a.enclosed
    value_to_send = 3
    enc = a.get(value_to_send)
    assert enc.c == 5 + value_to_send
    assert enc.c == a.enclosed.c

    value_to_send_2 = 7
    enc2 = a.get(value_to_send_2)
    assert enc2.c == 5 + value_to_send + value_to_send_2
    assert enc.c == 5 + value_to_send + value_to_send_2


def test_enclosed_class_2():
    a = myproj._example.TestBind()
    b = a.enclosed
    print(a.enclosed)
    print(a.enclosed.c)
    a.get(0)
    print(a.enclosed.c)
    a.get(1)
    print(a.enclosed.c)
    print("="*10)
    enc = a.get(6)
    print(a.enclosed.c)
    print(enc.c)
    print("="*5)
    enc2 = a.get(6)
    print(a.enclosed.c)
    print(enc2.c)
    print(enc.c)
    assert a.enclosed.c == 18
    assert enc2.c == 18
    assert enc.c == 18
