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
    value_to_send = 3
    enc = a.get(value_to_send)
    assert enc.c == 5 + value_to_send

    value_to_send_2 = 7
    enc2 = a.get(value_to_send_2)
    assert enc2.c == 5 + value_to_send + value_to_send_2
    assert enc.c == 5 + value_to_send + value_to_send_2
