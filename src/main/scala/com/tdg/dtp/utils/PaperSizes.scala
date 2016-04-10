package com.tdg.dtp.utils

object PaperSizes {

  val knownSizes = List(
    PaperSize("Legal", PaperCategory.Standard, 216,356),
    PaperSize("Junior Legal",PaperCategory.Standard, 127, 203),
    PaperSize("1/3 A4",PaperCategory.Standard, 99, 210),
    PaperSize("Gutenberg Bible",PaperCategory.Standard, 280, 398),
    PaperSize("CD case insert", PaperCategory.Standard, 120, 120),
    PaperSize("A4 square", PaperCategory.Standard, 210, 210),
    PaperSize("A format paperback", PaperCategory.Standard, 110, 178),
    PaperSize("B format paperback", PaperCategory.Standard, 130, 198),
    PaperSize("48 sheet billboard", PaperCategory.Standard,	6096, 3048),

    PaperSize("Business card (UK)", PaperCategory.BusinessCard, 55, 85),
    PaperSize("Business card (US)", PaperCategory.BusinessCard, 51, 89),
    PaperSize("Business card (Japan)", PaperCategory.BusinessCard, 55, 91),

    PaperSize("A0", PaperCategory.IntlA, 841, 1189),
    PaperSize("A1", PaperCategory.IntlA, 594, 841),
    PaperSize("A2", PaperCategory.IntlA, 420, 594),
    PaperSize("A3", PaperCategory.IntlA, 297, 420),
    PaperSize("A4", PaperCategory.IntlA, 210, 297),
    PaperSize("A5", PaperCategory.IntlA, 148, 210),
    PaperSize("A6", PaperCategory.IntlA, 105, 148),
    PaperSize("A7", PaperCategory.IntlA, 74, 105),
    PaperSize("A8", PaperCategory.IntlA, 52, 74),
    PaperSize("A9", PaperCategory.IntlA, 37, 52),
    PaperSize("A10", PaperCategory.IntlA, 26, 37)
  )

}

trait NamedElement {
  val name:String
}

/**
  * A class for storing common paper sizes
  *
  * @param name The name of the paper size
  * @param category The type of paper / usage
  * @param width width in mm
  * @param height height in mm
  */
sealed case class PaperSize(name:String,
                            category:PaperCategory,
                            width:Int, height:Int) extends NamedElement

/**
  * The various categories of paper
  * @param name A screen-displayable name
  */
sealed case class PaperCategory(name: String, tp:PaperType) extends NamedElement

object PaperCategory {
  object Standard extends PaperCategory("Standard", PaperType.Sheet)
  object BusinessCard extends PaperCategory("Business Card", PaperType.Sheet)
  object IntlA extends PaperCategory("International A", PaperType.Sheet)
  object USANSI extends PaperCategory("US ANSI", PaperType.Sheet)
}

sealed case class PaperType(name:String) extends NamedElement

object PaperType {
  object Sheet extends PaperType("Sheet")
  object Envelope extends PaperType("Envelope")
  object Roll extends PaperType("Roll")
}