import 'package:flutter/material.dart';

import './screens/home_screen.dart';

void main() {
  runApp(HungryCrabCompanion());
}

class HungryCrabCompanion extends StatelessWidget{
  @override
  Widget build(BuildContext context){
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: "Hungry Crab Companion",
      theme: ThemeData(
        primarySwatch: Colors.red,
        accentColor: Colors.blueAccent,
      ),
      home: HomeScreen(),
    );
  }
}

