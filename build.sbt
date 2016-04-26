lazy val commonSettings = Seq(
  organization := "com.thosedarngeeks",
  version := "0.1.0",
  scalaVersion := "2.11.8"
)

lazy val root = (project in file(".")).
  settings(commonSettings: _*).
  settings(
    name := "com.thosedarngeeks.dtp",
    scalacOptions ++= Seq("-g:vars","-verbose","-unchecked", "-deprecation", "-explaintypes"),
    libraryDependencies ++= Seq(
      "org.scala-lang" % "scala-reflect" % "2.11.8",
      "org.scala-lang.modules" % "scala-xml_2.11" % "1.0.4",
      "org.scalactic" %% "scalactic" % "2.2.6",
      "org.scalatest" %% "scalatest" % "2.2.6" % "test",
      "org.scalafx" %% "scalafx" % "8.0.60-R9",
      "org.eclipse.jgit" % "org.eclipse.jgit" % "4.3.0.201604071810-r",
      "com.h2database" % "h2" % "1.4.191",
      "ch.qos.logback" % "logback-classic" % "1.1.7",
      "com.chuusai" %% "shapeless" % "2.3.0"
    )
  )
