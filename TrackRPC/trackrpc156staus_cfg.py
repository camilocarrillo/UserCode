import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.RPCGeometry.rpcGeometry_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.0.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.1.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.2.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.3.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.4.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.5.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.6.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.7.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.8.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.9.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.10.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.11.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.12.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.13.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.14.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.15.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.16.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.17.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.18.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.19.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.20.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.21.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.22.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.23.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.24.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.25.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.26.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.27.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.28.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.29.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.30.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.31.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.32.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.33.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.34.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.35.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.36.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.37.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.38.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.39.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.40.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.41.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.42.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.43.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.44.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.45.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.46.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.47.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.48.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.49.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.50.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.51.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.52.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.53.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.54.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.55.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.56.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.57.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.58.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.59.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.60.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.61.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.62.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.63.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.64.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.65.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.66.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.67.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.68.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.69.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.70.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.71.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.72.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.73.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.74.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.75.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.76.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.77.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.78.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.79.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.80.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.81.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.82.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.83.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.84.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.85.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.86.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.87.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.88.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.89.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.90.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.91.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.92.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.93.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.94.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.95.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.96.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.97.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.98.root",
"rfio:/castor/cern.ch/user/c/carrillo/HSCP/STAU156_3_2_1/RECO/ROOT/STAU156_3_2_1_x10.99.root"
#       'file:/tmp/carrillo/kktau300GeVx1000WithRPC.root'
#        'file:/tmp/carrillo/mergedRECOstau156.root'
#        'file:/tmp/carrillo/STAU_10TeV_247_2_2_3_x1000.root'
#        'file:/tmp/carrillo/KKtau300_223_10TeV_2kevt.root'
    )
)

process.demo = cms.EDAnalyzer('TrackRPC',
  tracks = cms.untracked.string('standAloneMuons'),
  rootFileName = cms.untracked.string('/tmp/carrillo/hscpstaus156.root'),
  partLabel = cms.InputTag("generator"),

  ##kktaus
  #partid = cms.untracked.int32(-2000015) 

  ##staus
  partid = cms.untracked.int32(-1000015) 
  
)

process.p = cms.Path(process.demo)
