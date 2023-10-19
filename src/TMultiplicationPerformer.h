#ifndef TOPERATIONPERFORMER_H
#define TOPERATIONPERFORMER_H

#pragma once

namespace pmat {

class TMultiplicationManager;

class TMultiplicationPerformer {
   private:
      int _id;
      TMultiplicationManager *_manager{nullptr};
      int _row{0};
      int _column{0};

   public:
      TMultiplicationPerformer(int id, TMultiplicationManager &manager)
          : _id{id}, _manager{&manager} {}
      TMultiplicationPerformer(const TMultiplicationPerformer &) = default;
      TMultiplicationPerformer(TMultiplicationPerformer &&) = default;
      TMultiplicationPerformer &operator=(const TMultiplicationPerformer &) = default;
      TMultiplicationPerformer &operator=(TMultiplicationPerformer &&) = default;
      ~TMultiplicationPerformer() = default;

      void start();
      void setRowColumn(const int &row, const int &column);
};

} // namespace pmat

#endif