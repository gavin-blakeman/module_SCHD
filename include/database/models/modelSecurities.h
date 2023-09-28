#ifndef MODELSECURITIES_H
#define MODELSECURITIES_H

  // Standard C++ library

#include <vector>

  // msmERP

#include "include/core/typeDefinitions.h"
#include "include/database/models/modelAbstract.h"

class CApplication;

namespace models
{
  class CModelSecurities final : public CModelAbstract<index_t>
  {
  public:
    enum modelUsage_e
    {
      MU_NONE,
      MU_COMBO_NO_NULL,
      MU_COMBO_NULL,
      MU_TABLE,
    };

    CModelSecurities(CApplication &a, modelUsage_e mu, index_t &eid) : CModelAbstract(a), modelUsage(mu), exchangeID_(eid) {}
    virtual ~CModelSecurities() {}

    int symbol2Index(std::string const &);

    virtual std::any headerData(int section, Wt::Orientation orientation, Wt::ItemDataRole role) const override;
    virtual int columnCount(const Wt::WModelIndex &parent) const override;
    virtual int rowCount(const Wt::WModelIndex &parent) const override;
    virtual Wt::WModelIndex index(int row, int column, const Wt::WModelIndex &parent = Wt::WModelIndex()) const override;
    virtual Wt::WModelIndex parent(const Wt::WModelIndex &index) const override;
    virtual std::any data(const Wt::WModelIndex &index, Wt::ItemDataRole role) const override;
    virtual Wt::WFlags<Wt::ItemFlag> flags(const Wt::WModelIndex &index) const override;
    virtual void reload();

  private:
    CModelSecurities() = delete;
    CModelSecurities(int rows, int columns) = delete;
    CModelSecurities(CModelSecurities const &) = delete;
    CModelSecurities operator=(CModelSecurities const &) = delete;

    struct record_t
    {
      index_t ID;
      std::string shortText;
      std::string code;
      bool enabled;
    };

    modelUsage_e modelUsage;
    index_t &exchangeID_;
    std::vector<record_t> records_;

  };
}

#endif // MODELSECURITIES_H
