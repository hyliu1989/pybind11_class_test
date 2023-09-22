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
    # b = a.enclosed
    enc = a.get(6)
    enc2 = a.get(6)
    assert a.enclosed.c == 17
    assert enc2.c == 17
    assert enc.c == 17


def test_enclosed_class_2():
    a = myproj._example.TestBind()
    b = a.enclosed
    enc = a.get(6)
    enc2 = a.get(6)
    assert a.enclosed.c == 17
    assert enc2.c == 17
    assert enc.c == 17
