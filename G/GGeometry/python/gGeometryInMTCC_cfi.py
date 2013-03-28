import FWCore.ParameterSet.Config as cms

#
# This cfi should be included to build the G geometry model.
#
from Geometry.GGeometry.gGeometry_cfi import *
GGeometryESModule.compatibiltyWith11 = False

