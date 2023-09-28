#ifndef MODELFINANCIALYEARS_H
#define MODELFINANCIALYEARS_H

  // Standard C++ library

#include <map>
#include <string>
#include <vector>

  // Wt++

#include <Wt/WAbstractItemModel.h>

  // msmERP

#include "include/core/typeDefinitions.h"
#include "include/database/models/modelAbstract.h"

class CApplication;

namespace models
{
  class CModelFinancialYears: public CModelAbstract<index_t>
  {
  public:
    enum modelUsage_e
    {
      MU_NONE,
      MU_TABLE_NO_EDIT,
      MU_COMBO_NO_NULL,
    };

  private:
    CModelFinancialYears() = delete;
    CModelFinancialYears(int rows, int columns) = delete;
    CModelFinancialYears(CModelFinancialYears const &) = delete;
    CModelFinancialYears operator=(CModelFinancialYears const &) = delete;

    struct record_t
    {
      index_t ID;
      std::string shortText;
    };

    modelUsage_e modelUsage;
    std::vector<record_t> records_;

  protected:

  public:
    CModelFinancialYears(CApplication &a, modelUsage_e mu) : CModelAbstract(a), modelUsage(mu) {}
    virtual ~CModelFinancialYears() {}

    virtual std::any headerData(int section, Wt::Orientation orientation, Wt::ItemDataRole role) const;
    virtual int columnCount(const Wt::WModelIndex &parent) const;
    virtual int rowCount(const Wt::WModelIndex &parent) const;
    virtual Wt::WModelIndex index(int row, int column, const Wt::WModelIndex &parent = Wt::WModelIndex()) const;
    virtual Wt::WModelIndex parent(const Wt::WModelIndex &index) const;
    virtual std::any data(const Wt::WModelIndex &index, Wt::ItemDataRole role) const;
    virtual Wt::WFlags<Wt::ItemFlag> flags(const Wt::WModelIndex &index) const;
    virtual bool setData(Wt::WModelIndex const &index, std::any const &value, Wt::ItemDataRole role);
    virtual void reload();
  };

} // namespace

#endif // MODELFINANCIALYEARS_H
