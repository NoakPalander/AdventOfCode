def part1(filename: str) -> int:
    with open(filename, 'r') as reader:
        data = reader.readlines()

    x = y = 0
    faces = ['E', 'N', 'W', 'S']
    face = 'E'

    for instr in data:
        direction = instr[0]
        value = int(instr[1::])

        if direction == 'N':
            y += value

        elif direction == 'S':
            y -= value

        elif direction == 'E':
            x += value

        elif direction == 'W':
            x -= value

        elif direction == 'L':
            face = faces[(faces.index(face) + int(value / 90)) % 4]

        elif direction == 'R':
            face = faces[faces.index(face) - int(value / 90)]

        elif direction == 'F':
            if face == 'N':
                y += value
            elif face == 'S':
                y -= value
            elif face == 'E':
                x += value
            elif face == 'W':
                x -= value

    return abs(x) + abs(y)


def part2(filename: str) -> int:
    with open(filename, 'r') as reader:
        data = reader.readlines()

    waypoint = [ 10, 1 ]
    ship = [ 0, 0 ]

    for instr in data:
        direction = instr[0]
        value = int(instr[1::])

        if direction == 'N':
            waypoint[1] += value

        elif direction == 'S':
            waypoint[1] -= value

        elif direction == 'E':
            waypoint[0] += value

        elif direction == 'W':
            waypoint[0] -= value

        elif direction == 'R':
            for _ in range(int(value / 2)):
                x = waypoint[1]
                y = -waypoint[0]
                waypoint[0] = x
                waypoint[1] = y

        elif direction == 'L':
            for _ in range(int(value / 2)):
                x = -waypoint[1]
                y = waypoint[0]
                waypoint[0] = x
                waypoint[1] = y

        elif direction == 'F':
            ship[0] += waypoint[0] * value
            ship[1] += waypoint[1] * value

    return abs(ship[0]) + abs(ship[1])


def main():
    print(f'Part 1: {part1("input.txt")}')
    print(f'Part 2: {part2("input.txt")}')


if __name__ == '__main__':
    main()