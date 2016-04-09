/**
  * Created by garycoulbourne on 4/8/16.
  */
case class Rope(length: Long = 0,
                left: Option[Rope] = None,
                right: Option[Rope] = None,
                guts: String = "") {

  def +(that: Rope): Rope = new Rope(length + that.length, Some(this), Some(that))

  override def toString: String =
    (if (left.isEmpty && right.isEmpty) guts else "") +
    (if (left.isDefined) left.get.toString else "") +
    (if (right.isDefined) right.get.toString else "")

  def gc: Rope = ???

  def insert(loc: Long, str: Rope): Rope = ???
}

object Rope {

  val empty:Rope = new Rope

  def apply(in:String): Rope = new Rope(in.codePoints().count(),guts=in)

}
