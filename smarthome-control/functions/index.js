/**
 * Copyright 2018 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

'use strict';

const functions = require('firebase-functions');
const { smarthome } = require('actions-on-google');
const util = require('util');
const admin = require('firebase-admin');
// Initialize Firebase
admin.initializeApp();
const firebaseRef = admin.database().ref('/');

exports.fakeauth = functions.https.onRequest((request, response) => {
  const responseurl = util.format('%s?code=%s&state=%s',
    decodeURIComponent(request.query.redirect_uri), 'xxxxxx',
    request.query.state);
  console.log(responseurl);
  return response.redirect(responseurl);
});

exports.faketoken = functions.https.onRequest((request, response) => {
  const grantType = request.query.grant_type
    ? request.query.grant_type : request.body.grant_type;
  const secondsInDay = 86400; // 60 * 60 * 24
  const HTTP_STATUS_OK = 200;
  console.log(`Grant type ${grantType}`);

  let obj;
  if (grantType === 'authorization_code') {
    obj = {
      token_type: 'bearer',
      access_token: '123access',
      refresh_token: '123refresh',
      expires_in: secondsInDay,
    };
  } else if (grantType === 'refresh_token') {
    obj = {
      token_type: 'bearer',
      access_token: '123access',
      expires_in: secondsInDay,
    };
  }
  response.status(HTTP_STATUS_OK)
    .json(obj);
});

let jwt
try {
  jwt = require('./smart-home-key.json')
} catch (e) {
  console.warn('Service account key is not found')
  console.warn('Report state and Request sync will be unavailable')
}

const app = smarthome({
  jwt: jwt,
  debug: true,
})

let devicelist
devicelist = require('./devices.json')
const deviceitems = JSON.parse(JSON.stringify(devicelist));

var devicecounter;

app.onSync((body) => {
  for (devicecounter = 0; devicecounter < deviceitems.length; devicecounter++) {
    if (deviceitems[devicecounter].traits.includes('action.devices.traits.OnOff')) {
      firebaseRef.child(deviceitems[devicecounter].id).child('OnOff').set({ on: false });
    }
    if (deviceitems[devicecounter].traits.includes('action.devices.traits.Brightness')) {
      firebaseRef.child(deviceitems[devicecounter].id).child('Brightness').set({ brightness: 25 });
    }
    if (deviceitems[devicecounter].traits.includes('action.devices.traits.ColorSetting')) {
      firebaseRef.child(deviceitems[devicecounter].id).child('ColorSetting').set({ color: { name: "daylight", temperatureK: 5000 } });
    }
    if (deviceitems[devicecounter].traits.includes('action.devices.traits.LightEffects')) {
      firebaseRef.child(deviceitems[devicecounter].id).child('LightEffects').set({ activeLightEffect: "" });
    }
  }
  return {
    requestId: body.requestId,
    payload: {
      agentUserId: '123',
      devices: deviceitems
    },
  };
});


const queryFirebase = async (deviceId) => {
  const snapshot = await firebaseRef.child(deviceId).once('value');
  const snapshotVal = snapshot.val();

  var asyncvalue = {};

  if (Object.prototype.hasOwnProperty.call(snapshotVal, 'OnOff')) {
    asyncvalue = Object.assign(asyncvalue, { on: snapshotVal.OnOff.on });
  }
  if (Object.prototype.hasOwnProperty.call(snapshotVal, 'Brightness')) {
    asyncvalue = Object.assign(asyncvalue, { brightness: snapshotVal.Brightness.brightness });
  }
  if (Object.prototype.hasOwnProperty.call(snapshotVal, 'ColorSetting')) {
    asyncvalue = Object.assign(asyncvalue, { color: snapshotVal.ColorSetting.color });
  }
  if (Object.prototype.hasOwnProperty.call(snapshotVal, 'LightEffects')) {
    asyncvalue = Object.assign(asyncvalue, { activeLightEffect: snapshotVal.LightEffects.activeLightEffect });
  }
  return asyncvalue;
}

const queryDevice = async (deviceId) => {
  const data = await queryFirebase(deviceId);

  var datavalue = {};

  if (Object.prototype.hasOwnProperty.call(data, 'on')) {
    datavalue = Object.assign(datavalue, { on: data.on });
  }
  if (Object.prototype.hasOwnProperty.call(data, 'brightness')) {
    datavalue = Object.assign(datavalue, { brightness: data.brightness });
  }
  if (Object.prototype.hasOwnProperty.call(data, 'color')) {
    datavalue = Object.assign(datavalue, { color: data.color });
  }
  if (Object.prototype.hasOwnProperty.call(data, 'activeLightEffect')) {
    datavalue = Object.assign(datavalue, { activeLightEffect: data.activeLightEffect });
  }
  return datavalue;
}

app.onQuery(async (body) => {
  const { requestId } = body;
  const payload = {
    devices: {},
  };

  const queryPromises = [];
  const intent = body.inputs[0];
  for (const device of intent.payload.devices) {
    const deviceId = device.id;
    queryPromises.push(queryDevice(deviceId)
      .then((data) => {
        // Add response to device payload
        payload.devices[deviceId] = data;
      }
      ));
  }
  // Wait for all promises to resolve
  await Promise.all(queryPromises)
  return {
    requestId: requestId,
    payload: payload,
  };
});

const updateDevice = async (execution, deviceId) => {
  const { params, command } = execution;
  let state, ref;
  switch (command) {
    case 'action.devices.commands.OnOff':
      state = { on: params.on };
      ref = firebaseRef.child(deviceId).child('OnOff');
      break;
    case 'action.devices.commands.BrightnessAbsolute':
      state = { brightness: params.brightness };
      ref = firebaseRef.child(deviceId).child('Brightness');
      break;
    case 'action.devices.commands.ColorAbsolute':
      state = { color: params.color };
      ref = firebaseRef.child(deviceId).child('ColorSetting');
      break;
    case 'action.devices.commands.ColorLoop':
      state = { activeLightEffect: params.activeLightEffect };
      ref = firebaseRef.child(deviceId).child('LightEffects');
      break;
    case 'action.devices.commands.Sleep':
      state = { activeLightEffect: params.activeLightEffect };
      ref = firebaseRef.child(deviceId).child('LightEffects');
      break;
    case 'action.devices.commands.StopEffect':
      state = { activeLightEffect: params.activeLightEffect };
      ref = firebaseRef.child(deviceId).child('LightEffects');
      break;
    case 'action.devices.commands.Wake':
      state = { activeLightEffect: params.activeLightEffect };
      ref = firebaseRef.child(deviceId).child('LightEffects');
      break;
  }
  return ref.update(state)
    .then(() => state);
};

app.onExecute(async (body) => {
  const { requestId } = body;
  // Execution results are grouped by status
  const result = {
    ids: [],
    status: 'SUCCESS',
    states: {
      online: true,
    },
  };

  const executePromises = [];
  const intent = body.inputs[0];
  for (const command of intent.payload.commands) {
    for (const device of command.devices) {
      for (const execution of command.execution) {
        executePromises.push(
          updateDevice(execution, device.id)
            .then((data) => {
              result.ids.push(device.id);
              Object.assign(result.states, data);
            })
            .catch(() => console.error(`Unable to update ${device.id}`))
        );
      }
    }
  }

  await Promise.all(executePromises)
  return {
    requestId: requestId,
    payload: {
      commands: [result],
    },
  };
});


exports.smarthome = functions.https.onRequest(app);

exports.requestsync = functions.https.onRequest(async (request, response) => {
  response.set('Access-Control-Allow-Origin', '*');
  console.info('Request SYNC for user 123');
  try {
    const res = await app.requestSync('123');
    console.log('Request sync completed');
    response.json(res.data);
  } catch (err) {
    console.error(err);
    response.status(500).send(`Error requesting sync: ${err}`)
  }
});

/**
 * Send a REPORT STATE call to the homegraph when data for any device id
 * has been changed.
 */
exports.reportstate = functions.database.ref('{deviceId}').onWrite(async (change, context) => {
  console.info('Firebase write event triggered this cloud function');
  if (!app.jwt) {
    console.warn('Service account key is not configured');
    console.warn('Report state is unavailable');
    return;
  }
  const snapshot = change.after.val();

  var syncvalue = {};

  if (Object.prototype.hasOwnProperty.call(snapshot, 'OnOff')) {
    syncvalue = Object.assign(syncvalue, { on: snapshot.OnOff.on });
  }
  if (Object.prototype.hasOwnProperty.call(snapshot, 'Brightness')) {
    syncvalue = Object.assign(syncvalue, { brightness: snapshot.Brightness.brightness });
  }
  if (Object.prototype.hasOwnProperty.call(snapshot, 'ColorSetting')) {
    syncvalue = Object.assign(syncvalue, { color: snapshot.ColorSetting.color });
  }
  if (Object.prototype.hasOwnProperty.call(snapshot, 'LightEffects')) {
    syncvalue = Object.assign(syncvalue, { activeLightEffect: snapshot.LightEffects.activeLightEffect });
  }

  const postData = {
    requestId: 'ff36a3ccsiddhy', /* Any unique ID */
    agentUserId: '123', /* Hardcoded user ID */
    payload: {
      devices: {
        states: {
          /* Report the current state of our light */
          [context.params.deviceId]: syncvalue,
        },
      },
    },
  };

  const data = await app.reportState(postData);
  console.log('Report state came back');
  console.info(data);
});
