import org.scalatest._

class RopeTest extends FlatSpec {

  "A Rope" should "have a length matching the number of ASCII characters in it" in {
    val r = Rope("This is a rope")
    assert(r.length == 14)
  }

  "A Rope" should "be able to be added together" in {
    val a = Rope("Happy ") + Rope("Birthday")
    assert(a.length == 14)
    assert(a.toString == "Happy Birthday")

    val b = a + Rope(" to you!")
    assert(b.length == 22)
    assert(b.toString == "Happy Birthday to you!")

    val c = ('a' to 'z').map(x => Rope(x.toString)).foldLeft(Rope.empty)( (x,y) => x + y )
    assert(c.length == 26)
    assert(c.toString == "abcdefghijklmnopqrstuvwxyz")
  }

}
