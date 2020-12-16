import java.io.File

fun read(filename: String) = File(filename).readLines()[0].split(",")
    .filterNot { it.isEmpty() || it.isBlank() }
    .map { it.toInt() }
    .toMutableList()


fun part1(filename: String): Number {
    val hist = read(filename).mapIndexed { idx, item -> Pair(item, idx) }.toMutableList()

    for (index in hist.size until 2020) {
        // First time
        if (hist.count{ it.first == hist.last().first } == 1)
            hist.add(Pair(0, index))

        // Previously seen
        else {
            val firstLast = hist.filter { it.first == hist.last().first }.let { it[it.lastIndex - 1] }.second
            val secondLast = hist.last { it.first == hist.last().first }.second

            hist.add(Pair(if(secondLast - firstLast != 1) secondLast - firstLast else 1, index))
        }
    }

    return hist.last().first
}

fun part2(filename: String): Number {
    fun HashMap<Int, MutableList<Int>>.addOrExtend(key: Int, value: Int) {
        if (this.contains(key))
            this[key]!!.add(value)
        else
            this[key] = mutableListOf(value)
    }

    val data = read(filename)
    val targets = hashMapOf<Int, MutableList<Int>>()
    data.forEachIndexed { index, value -> targets[value] = mutableListOf(index) }
    var last = data.last()

    for (index in data.size until 30000000) {
        // First time
        if (targets.contains(last) && targets[last]!!.size == 1) {
            last = 0
            targets.addOrExtend(0, index)
        }
        // Previously seen
        else {
            val indices = targets[last]!!
            val diff = indices[indices.size - 1] - indices[indices.size - 2]
            val say = if(diff != 1) diff else 1

            last = say
            targets.addOrExtend(say, index)
        }
    }

    return last
}

fun main() {
    println("Part 1: ${part1("input.txt")}")
    println("Part 2: ${part2("input.txt")}")
}