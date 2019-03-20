#!/usr/bin/env python3

from math import sqrt
import click
from PIL import Image

MAX_SIZE = 69, 69

@click.command()
@click.argument("file", type=click.Path(exists=True, readable=True))
@click.option("--max", default=5000, help="Maximum number of particles")
def main(file, max):
    """
    Convert an image into positions of particles and speed.
    """

    logo = Image.open(file).convert("RGB")
    maxi = sqrt(max)
    logo.thumbnail((maxi, maxi))

    parts = []

    X, Y = logo.size
    for y in range(Y):
        for x in range(X):
            r, g, b = logo.getpixel((x, y))
            # normalize the positions (between -1 and 1 for x, and y follows)
            norm_x = 2*x / X - 1
            norm_y = 2*y / X - 1
            # position then color
            parts.append((norm_x, -norm_y, 0, r / 255, g / 255, b / 255))

    print(len(parts))
    for p in parts:
        print(*p)


if __name__ == '__main__':
    main()
