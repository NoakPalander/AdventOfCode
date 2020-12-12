import java.io.File

fun readInput(filename: String) = File(filename).readLines()

fun part1(filename: String): Int {
    val data = readInput(filename).map { it.toList() }

    fun occupied(seats: List<List<Char>>, pos: Pair<Int, Int>, seat: Char): List<Char> {
        return seats.filterIndexed { y, _ -> y in pos.second - 1..pos.second + 1 }
                .flatMap { it.filterIndexed { x, _ ->  x in pos.first - 1..pos.first + 1 } }
                .minus(seat)
                .filter { it == '#' }
    }

    var before: List<List<Char>>
    var after = listOf<List<Char>>()
    do {
        before = after.ifEmpty { data }
        after = before.mapIndexed { y, row ->
            row.mapIndexed { x, seat ->
                val adjSeats = occupied(before, Pair(x, y), seat)
                when {
                    seat == '.' -> '.'
                    adjSeats.isEmpty() -> '#'
                    adjSeats.size >= 4 -> 'L'
                    else -> seat
                }
            }
        }
    } while (before != after)

    return after.flatten().filter { it == '#' }.size
}

fun part2(filename: String): Int {
    val data = readInput(filename).map { it.toList() }

    fun occupied(seats: List<List<Char>>, pos: Pair<Int, Int>): List<Char> {
        return listOf(
            Pair(0, -1),
            Pair(0, 1),
            Pair(-1, 0),
            Pair(-1, 1),
            Pair(-1, -1),
            Pair(1, 0),
            Pair(1, 1),
            Pair(1, -1)
        ).mapNotNull { dir ->
            var (x, y) = pos
            var adj: Char? = '.'
            do {
                x += dir.first
                y += dir.second
                adj = seats.getOrNull(y)?.getOrNull(x)
            } while (adj == '.')
            adj
        }.filter { it == '#' }
    }

    var before: List<List<Char>>
    var after =  listOf<List<Char>>()
    do {
        before = after.ifEmpty { data }
        after = before.mapIndexed { y, row ->
            row.mapIndexed { x, seat ->
                val occupiedAdjacentSeats = occupied(before, Pair(x, y))
                when {
                    seat == '.' -> '.'
                    occupiedAdjacentSeats.isEmpty() -> '#'
                    occupiedAdjacentSeats.size >= 5 -> 'L'
                    else -> seat
                }
            }
        }
    } while (before != after)

    return after.flatten().filter { it == '#' }.size
}

fun main() {
    println("Part 1: ${part1("input.txt")}")
    println("Part 21: ${part2("input.txt")}")
}