///
///  \file   MMHit.hh
///
///  \author Christopher Rogan
///          (crogan@cern.ch)
///
///  \date   2016 Sept
///


#ifndef MMHit_HH
#define MMHit_HH

class MMHit {

public:
  MMHit();
  MMHit(const MMHit& hit);
  ~MMHit();

  int VMM() const;
  int Channel() const;
  int VMMChannel() const;
  int PDO() const;
  int TDO() const;
  int BCID() const;
  int MMFE8() const;
  int FIFOcount() const;

  double Charge() const;
  double Time() const;
  
private:
  int m_MMFE8;
  int m_VMM;
  int m_CH;
  int m_PDO;
  int m_TDO;
  int m_BCID;
  int m_FIFOcount;

  double m_charge;
  double m_time; 
};

#endif

inline MMHit::MMHit(){
  m_MMFE8 = -1;
  m_VMM = -1;
  m_CH = -1;
  m_PDO = -1;
  m_TDO = -1;
  m_BCID = -1;
  m_FIFOcount = -1;

  m_charge;
  m_time; 
}

inline MMHit::MMHit(const MMHit& hit){
  m_MMFE8 = hit.MMFE8();
  m_VMM = hit.VMM();
  m_CH = hit.VMMChannel();
  m_PDO = hit.PDO();
  m_TDO = hit.TDO();
  m_BCID = hit.BCID();
  m_FIFOcount = hit.FIFOcount();

  m_charge = hit.Charge();
  m_time = hit.Time(); 
}
  
inline MMHit::~MMHit(){

}

inline int MMHit::MMFE8() const {
  return m_MMFE8;
}

inline int MMHit::VMM() const {
  return m_VMM;
}

inline int MMHit::Channel() const {
  return std::max(-1,64*m_VMM + m_CH);
}

inline int MMHit::VMMChannel() const {
  return m_CH;
}

inline int MMHit::PDO() const {
  return m_PDO;
}

inline int MMHit::TDO() const {
  return m_TDO;
}

inline int MMHit::BCID() const {
  return m_BCID;
}

inline int MMHit::FIFOcount() const {
  return m_FIFOcount;
}

inline double MMHit::Charge() const {
  return m_charge;
}

inline double MMHit::Time() const {
  return m_time;
}

