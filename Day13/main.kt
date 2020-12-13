import java.io.File
import kotlin.math.ceil

fun part1(filename: String): Int {
    val raw = File(filename).readLines()
    val timestamp = raw[0].toInt()
    val ids = raw[1].split(",").filterNot { it == "x" }.map { it.toInt() }

    return ids.map {
        it to ceil(timestamp.toFloat() / it).toInt() * it - timestamp
    }.minByOrNull { it.second }?.let { it.second * it.first } ?: throw RuntimeException("Unsolved!")
}

fun part2(filename: String): Long {
    val ids = File(filename).readLines()[1].split(",")
            .mapIndexed { index, str -> Pair(index, str) }
            .filterNot { it.second == "x" }
            .map { Pair(it.first, it.second.toInt()) }

    var step = ids[0].second.toLong()
    var time = 0L

    ids.drop(1).forEach { (diff, id) ->
        while ((time + diff) % id != 0L)
            time += step

        step *= id
    }

    return time
}

fun main() {
    println("Part 1: ${part1("input.txt")}")
    println("Part 2: ${part2("input.txt")}")
}