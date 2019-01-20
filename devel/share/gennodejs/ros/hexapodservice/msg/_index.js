
"use strict";

let legs = require('./legs.js');
let legjoint = require('./legjoint.js');
let legjoints = require('./legjoints.js');
let leg = require('./leg.js');
let hexapodserviceAction = require('./hexapodserviceAction.js');
let hexapodserviceActionFeedback = require('./hexapodserviceActionFeedback.js');
let hexapodserviceFeedback = require('./hexapodserviceFeedback.js');
let hexapodserviceGoal = require('./hexapodserviceGoal.js');
let hexapodserviceActionGoal = require('./hexapodserviceActionGoal.js');
let hexapodserviceResult = require('./hexapodserviceResult.js');
let hexapodserviceActionResult = require('./hexapodserviceActionResult.js');

module.exports = {
  legs: legs,
  legjoint: legjoint,
  legjoints: legjoints,
  leg: leg,
  hexapodserviceAction: hexapodserviceAction,
  hexapodserviceActionFeedback: hexapodserviceActionFeedback,
  hexapodserviceFeedback: hexapodserviceFeedback,
  hexapodserviceGoal: hexapodserviceGoal,
  hexapodserviceActionGoal: hexapodserviceActionGoal,
  hexapodserviceResult: hexapodserviceResult,
  hexapodserviceActionResult: hexapodserviceActionResult,
};
