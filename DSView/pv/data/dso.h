/*
 * This file is part of the DSView project.
 * DSView is based on PulseView.
 *
 * Copyright (C) 2013 DreamSourceLab <support@dreamsourcelab.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */


#ifndef DSVIEW_PV_DATA_DSO_H
#define DSVIEW_PV_DATA_DSO_H

#include "signaldata.h"
 
#include <deque>

namespace pv {
namespace data {

class DsoSnapshot;

class Dso : public SignalData
{
public:
    Dso(DsoSnapshot *snapshot);

	void push_snapshot(DsoSnapshot *snapshot);

    std::deque<DsoSnapshot*>& get_snapshots();

    void clear();
    void init();

    DsoSnapshot* snapshot();

private:
    std::deque<DsoSnapshot*> _snapshots;
};

} // namespace data
} // namespace pv

#endif // DSVIEW_PV_DATA_DSO_H
