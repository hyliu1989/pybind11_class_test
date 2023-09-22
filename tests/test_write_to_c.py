import myproj._example


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
