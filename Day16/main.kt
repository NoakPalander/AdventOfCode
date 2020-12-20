import java.io.File

fun part1(nearbyFile: String, rangesFile: String): Number {
    val nearby = File(nearbyFile).readLines().map { line -> line.split(",").map { it.toInt() } }.flatten().toMutableList()
    val ranges = File(rangesFile).readLines().map { it.substring(it.indexOf(':') + 2).split(" or ") }.flatten()

    val valid = mutableListOf<Int>()
    nearby.forEach numbers@ { value ->
        ranges.forEach { range ->
            val (min, max) = range.split("-").map { it.toInt() }
            if (value in min..max) {
                valid.add(value)
                return@numbers
            }
        }
    }

    nearby.removeAll(valid)
    return nearby.sum()
}

fun main() {
    println("Part 1: ${part1("nearby.txt", "ranges.txt")}")
}