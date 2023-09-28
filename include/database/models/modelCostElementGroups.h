#ifndef MODELCOSTELEMENTGROUPS_H
#define MODELCOSTELEMENTGROUPS_H

  // Standard C++ library

#include <vector>

  // msmERP

#include "include/core/typeDefinitions.h"
#include "include/database/models/modelAbstract.h"

class CApplication;

namespace models
{
  class CModelCostElementGroups: public CModelAbstract<index_t>
  {
  public:
    enum modelUsage_e
    {
      MU_NONE,
      MU_COMBO,
      MU_TABLE_EDIT,
    };
  private:
    CModelCostElementGroups() = delete;
    CModelCostElementGroups(int rows, int columns) = delete;
    CModelCostElementGroups(CModelCostElementGroups const &) = delete;
    CModelCostElementGroups operator=(CModelCostElementGroups const &) = delete;

    struct record_t
    {
      index_t ID;
      std::string shortText;
      bool enabled;
    };

    modelUsage_e modelUsage;
    std::vector<record_t> records_;
    index_t reasonID_;

  protected:

  public:
    CModelCostElementGroups(CApplication &a, modelUsage_e mu) : CModelAbstract(a), modelUsage(mu) {}
    virtual ~CModelCostElementGroups() {}

    virtual std::any headerData(int section, Wt::Orientation orientation, Wt::ItemDataRole role) const override;
    virtual int columnCount(const Wt::WModelIndex &parent) const override;
    virtual int rowCount(const Wt::WModelIndex &parent) const override;
    virtual Wt::WModelIndex index(int row, int column, const Wt::WModelIndex &parent = Wt::WModelIndex()) const override;
    virtual Wt::WModelIndex parent(const Wt::WModelIndex &index) const override;
    virtual std::any data(const Wt::WModelIndex &index, Wt::ItemDataRole role) const override;
    virtual Wt::WFlags<Wt::ItemFlag> flags(const Wt::WModelIndex &index) const override;
    virtual bool setData(Wt::WModelIndex const &index, std::any const &value, Wt::ItemDataRole role) override;
    virtual void reload(index_t);

  };
}

#endif // MODELCOSTELEMENTGROUPS_H
