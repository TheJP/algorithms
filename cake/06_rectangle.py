def get_between1(a1: int, a2: int, b1: int, b2: int):
    if b1 <= a1 <= b2:
        return a1
    elif a1 <= b1 <= a2:
        return b1
    else:
        return None


def get_between2(a1: int, a2: int, b1: int, b2: int):
    if b1 <= a2 <= b2:
        return a2
    elif a1 <= b2 <= a2:
        return b2
    else:
        return None


class Rectangle:
    def __init__(self, x: int, y: int, w: int, h: int):
        self.x = x
        self.y = y
        self.w = w
        self.h = h

    def __str__(self):
        return "({}, {}) + ({}, {})".format(self.x, self.y, self.w, self.h)

    def intersect(self, other):
        x = get_between1(self.x, self.x + self.w, other.x, other.x + other.w)
        y = get_between1(self.y, self.y + self.h, other.y, other.y + other.h)
        w = get_between2(self.x, self.x + self.w, other.x, other.x + other.w)
        h = get_between2(self.y, self.y + self.h, other.y, other.y + other.h)
        if x is None or y is None or w is None or h is None or x == w or y == h:
            return None
        return Rectangle(x, y, w - x, h - y)


def rectangle(x, y, w, h):
    return dict(left_x=x, bottom_y=y, width=w, height=h)


def better(dictionary):
    return Rectangle(dictionary["left_x"], dictionary["bottom_y"], dictionary["width"], dictionary["height"])


print(Rectangle(0, 0, 4, 4).intersect(Rectangle(8, 2, 4, 4)))
print(Rectangle(0, 0, 4, 4).intersect(Rectangle(2, 2, 4, 4)))
print(Rectangle(0, 2, 4, 4).intersect(Rectangle(2, 0, 4, 4)))
print(Rectangle(0, 2, 8, 8).intersect(Rectangle(2, 0, 4, 4)))
print(Rectangle(2, 0, 4, 4).intersect(Rectangle(0, 2, 8, 8)))
print(Rectangle(0, 0, 8, 8).intersect(Rectangle(2, 2, 4, 4)))
print(Rectangle(0, 0, 4, 4).intersect(Rectangle(0, 0, 4, 4)))
print(Rectangle(2, 0, 2, 8).intersect(Rectangle(0, 2, 8, 2)))
print(Rectangle(0, 0, 4, 4).intersect(Rectangle(4, 2, 4, 4)))
print(Rectangle(0, 0, 4, 4).intersect(Rectangle(0, 0, 2, 2)))
