lazy val commonSettings = Seq(
  organization := "com.thosedarngeeks",
  version := "0.1.0",
  scalaVersion := "2.11.8",
  resolvers += "Artima Maven Repository" at "http://repo.artima.com/releases"
  //addSbtPlugin("com.artima.supersafe" % "sbtplugin" % "1.1.0-RC6")
)

lazy val root = (project in file(".")).
  settings(commonSettings: _*).
  settings(
    name := "com.tdg.dtp.utils.Rope",
    libraryDependencies ++= Seq(
      "org.scala-lang" % "scala-reflect" % "2.11.8",
      "org.scala-lang.modules" % "scala-xml_2.11" % "1.0.4",
      "org.scalactic" %% "scalactic" % "2.2.6",
      "org.scalatest" %% "scalatest" % "2.2.6" % "test"
    )
  )
