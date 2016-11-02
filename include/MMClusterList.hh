///
///  \file   MMClusterList.hh
///
///  \author Christopher Rogan
///          (crogan@cern.ch)
///
///  \date   2016 Sept
///


#ifndef MMClusterList_HH
#define MMClusterList_HH

#include "include/MMCluster.hh"
using namespace std;

class MMClusterList {

public:
  MMClusterList();
  MMClusterList(const MMCluster& clus);
  MMClusterList(const MMClusterList& cl);
  
  ~MMClusterList();

  void AddCluster(const MMCluster& clus);
  void AddHit(const MMHit& hit, int iclus);
  void AddLinkedHit(const MMLinkedHit& hit, int iclus);
  
  int GetNCluster() const;
  MMCluster const& Get(int i) const;
  MMCluster const& operator [] (int i) const;

  int GetNDuplicates() const;
  void ClearClusters();

  bool Contains(const MMHit& hit) const;

  vector<MMCluster> GetBoardClusters(int MMFE8) const;
private:
  std::vector<MMCluster*> m_clusters;
  
};

inline MMClusterList::MMClusterList() {}

inline MMClusterList::MMClusterList(const MMCluster& clus){
  AddCluster(clus);
}

inline MMClusterList::MMClusterList(const MMClusterList& cl){
  int N = cl.GetNCluster();
  for(int i = 0; i < N; i++)
    AddCluster(cl[i]);
}
  
inline MMClusterList::~MMClusterList(){
    ClearClusters();
}

inline void MMClusterList::ClearClusters() {
  int N = GetNCluster();
  for(int i = 0; i < N; i++)
    delete m_clusters[i];
  m_clusters.clear();
}

inline void MMClusterList::AddCluster(const MMCluster& clus){
  int N = GetNCluster();
  for(int i = 0; i < N; i++){
    if(clus.Charge() > m_clusters[i]->Charge()){
      m_clusters.insert(m_clusters.begin()+i, new MMCluster(clus));
      return;
    }
  }
  m_clusters.push_back(new MMCluster(clus));
}

inline void MMClusterList::AddHit(const MMHit& hit, int iclus){
  if(iclus < 0 || iclus >= GetNCluster())
    return;

  m_clusters[iclus]->AddHit(hit);
}

inline void MMClusterList::AddLinkedHit(const MMLinkedHit& hit, int iclus){
  if(iclus < 0 || iclus >= GetNCluster())
    return;

  m_clusters[iclus]->AddLinkedHit(hit);
}
  
inline int MMClusterList::GetNCluster() const {
  return m_clusters.size();
}

inline MMCluster const& MMClusterList::Get(int i) const {
  return *m_clusters[i];
}

inline MMCluster const& MMClusterList::operator [] (int i) const {
  return Get(i);
}

int MMClusterList::GetNDuplicates() const {
  int Ndup = 0;
  int Nclus = GetNCluster();
  for(int i = 0; i < Nclus; i++)
    if(m_clusters[i]->GetNDuplicates() > 0)
      Ndup++;
  return Ndup;
}

inline bool MMClusterList::Contains(const MMHit& hit) const {
  int Nclus = GetNCluster();
  for(int i = 0; i < Nclus; i++)
    if(m_clusters[i]->Contains(hit))
      return true;
  return false;
}

inline vector<MMCluster> MMClusterList::GetBoardClusters(int MMFE8) const {
  vector<MMCluster> ret;
  int Nclus = GetNCluster();
  for (int i = 0; i < Nclus; i ++) {
      if (m_clusters[i]->MMFE8() == MMFE8) {
        ret.push_back( *m_clusters[i] );
      }
  }
  return ret;


}

#endif




