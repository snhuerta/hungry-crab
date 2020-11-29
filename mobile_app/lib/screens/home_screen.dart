import 'dart:convert';

import 'package:control_pad/models/gestures.dart';
import 'package:control_pad/models/pad_button_item.dart';
import 'package:flutter/services.dart';
import 'package:control_pad/control_pad.dart';
import 'package:flutter/material.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';

class HomeScreen extends StatefulWidget {
  @override
  _HomeScreenState createState() {
    return _HomeScreenState();
  }
}

class _HomeScreenState extends State<HomeScreen> {
  BluetoothConnection connection;
  void toggleConnect() {
    if (connection == null || !connection.isConnected) {
      try {
        BluetoothConnection.toAddress("24:6F:28:9D:AB:76").then((connection) {
          setState(() {
            this.connection = connection;
          });
        });
        print('Connected to the device');
        // connection.output.add(utf8.encode("12" + "\r\n"));
        // await connection.output.allSent;
      } catch (exception) {
        print('Cannot connect, exception occured');
      }
    } else {
      connection.finish().then((connection) {
        setState(() {});
      });
      print('Disconnected from the device');
    }
  }

  @override
  Widget build(BuildContext context) {
    SystemChrome.setPreferredOrientations(
        [DeviceOrientation.landscapeLeft, DeviceOrientation.landscapeRight]);

    // connect();
    return Scaffold(
      appBar: AppBar(
        title: Text("Hungry Crab Companion"),
        actions: [
          IconButton(
            icon: Icon(
              connection == null || !connection.isConnected
                  ? Icons.bluetooth_rounded
                  : Icons.bluetooth_connected_rounded,
            ),
            onPressed: toggleConnect,
          ),
        ],
      ),
      body: Row(
        mainAxisAlignment: MainAxisAlignment.spaceAround,
        children: [
          JoystickView(onDirectionChanged: (ang, r) async {
            print('a${ang.round()}');
            connection.output
                .add(utf8.encode('a${ang.round()},${r.round()}\r\n'));
            await connection.output.allSent;
          }),
          PadButtonsView(
            backgroundPadButtonsColor: Colors.grey,
            buttonsPadding: 7,
            buttons: [
              PadButtonItem(
                index: 0,
                buttonIcon: Icon(Icons.play_for_work_rounded),
                backgroundColor: Colors.green,
                pressedColor: Colors.grey,
                supportedGestures: [
                  Gestures.LONGPRESSSTART,
                  Gestures.LONGPRESSUP
                ],
              ),
              PadButtonItem(
                index: 1,
                buttonIcon: Icon(Icons.rotate_left_rounded),
                backgroundColor: Colors.yellow,
                pressedColor: Colors.grey,
                supportedGestures: [
                  Gestures.LONGPRESSSTART,
                  Gestures.LONGPRESSUP
                ],
              ),
              PadButtonItem(
                index: 2,
                buttonIcon: Icon(Icons.rotate_right_rounded),
                backgroundColor: Colors.blue,
                pressedColor: Colors.grey,
                supportedGestures: [
                  Gestures.LONGPRESSSTART,
                  Gestures.LONGPRESSUP
                ],
              ),
              PadButtonItem(
                index: 3,
                buttonIcon: Icon(Icons.stop),
                backgroundColor: Colors.red,
                pressedColor: Colors.grey,
                supportedGestures: [
                  Gestures.LONGPRESSSTART,
                  Gestures.LONGPRESSUP
                ],
              ),
            ],
            padButtonPressedCallback: (index, gestures) async {
              print(
                  'b$index, ${gestures == Gestures.LONGPRESSSTART}, ${gestures == Gestures.LONGPRESSUP}');
              connection.output.add(ascii.encode(
                  'b$index,${gestures == Gestures.LONGPRESSSTART},${gestures == Gestures.LONGPRESSUP}\r\n'));
              await connection.output.allSent;
            },
          ),
        ],
      ),
    );
  }
}
