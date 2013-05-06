import FWCore.ParameterSet.Config as cms

#
# This cfi should be included to build the G geometry model.
#
GGeometryESModule = cms.ESProducer("GGeometryESModule",
    compatibiltyWith11 = cms.untracked.bool(True),
    useDDD = cms.untracked.bool(True)
)

