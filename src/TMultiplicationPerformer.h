#ifndef TOPERATIONPERFORMER_H
#define TOPERATIONPERFORMER_H

#pragma once

namespace pmat {

class TMultiplicationManager;

class TMultiplicationPerformer {
   private:
      unsigned _id;
      TMultiplicationManager *_manager{nullptr};
      unsigned _row{0};
      unsigned _column{0};

   public:
      TMultiplicationPerformer(unsigned id, TMultiplicationManager &manager)
          : _id{id}, _manager{&manager} {}
      TMultiplicationPerformer(const TMultiplicationPerformer &) = default;
      TMultiplicationPerformer(TMultiplicationPerformer &&) = default;
      TMultiplicationPerformer &operator=(const TMultiplicationPerformer &) = default;
      TMultiplicationPerformer &operator=(TMultiplicationPerformer &&) = default;
      ~TMultiplicationPerformer() = default;

      void start();
      void setRowColumn(const unsigned &row, const unsigned &column);
};

} // namespace pmat

#endif