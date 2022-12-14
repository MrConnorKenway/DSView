/*
 * This file is part of the DSView project.
 * DSView is based on PulseView.
 *
 * Copyright (C) 2013 Joel Holdsworth <joel@airwebreathe.org.uk>
 * Copyright (C) 2014 DreamSourceLab <support@dreamsourcelab.com>
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

#ifndef DSVIEW_PV_VIEW_TRACE_H
#define DSVIEW_PV_VIEW_TRACE_H

#include <QColor>
#include <QPainter>
#include <QPen>
#include <QRect>
#include <QString>

#include <stdint.h>

#include "selectableitem.h"
#include "dsldial.h"

class QFormLayout;

namespace pv {
namespace view {

class View;
class Viewport;

//base class
class Trace : public SelectableItem
{
	Q_OBJECT

protected:
    static const int Margin = 3;
    static const int SquareNum = 5;
	static const int LabelHitPadding;

public:
    static const int SquareWidth = 20;
    static const int COLOR = 1;
    static const int NAME = 2;
    static const int LABEL = 8;

    static const QColor PROBE_COLORS[8];

protected:
    Trace(QString name, uint16_t index, int type);
    Trace(QString name, std::list<int> index_list, int type, int sec_index);

    /**
     * Copy constructor
     */
    Trace(const Trace &t);

public:
	/**
	 * Gets the name of this signal.
	 */
	QString get_name();
    virtual int get_name_width();

	/**
	 * Sets the name of the signal.
	 */
	virtual void set_name(QString name);

	/**
	 * Get the colour of the signal.
	 */
	QColor get_colour();

	/**
	 * Set the colour of the signal.
	 */
	void set_colour(QColor colour);

	/**
	 * Gets the vertical layout offset of this signal.
	 */
	int get_v_offset();

	/**
	 * Sets the vertical layout offset of this signal.
	 */
	void set_v_offset(int v_offset);

    /**
     * Gets trace type
     */
    int get_type();

    /**
     * Index process
     */
    int get_index();
    std::list<int> &get_index_list();
    void set_index_list(std::list<int> index_list);
    int get_sec_index();
    void set_sec_index(int sec_index);

    /**
     * Gets the height of this signal.
     */
    int get_totalHeight();

    /**
     * Sets the height of this signal.
     */
    void set_totalHeight(int height);

    /**
     * Geom
     */
    int get_leftWidth();
    int get_rightWidth();
    int get_headerHeight();

    /**
     * Gets the old vertical layout offset of this signal.
     */
    int get_old_v_offset();

    /**
     * Sets the old vertical layout offset of this signal.
     */
    void set_old_v_offset(int v_offset);

    virtual int get_zero_vpos();

	/**
	 * Returns true if the trace is visible and enabled.
	 */
    virtual bool enabled() = 0;

	virtual void set_view(pv::view::View *view);
    pv::view::View* get_view();
    virtual void set_viewport(pv::view::Viewport *viewport);
    pv::view::Viewport* get_viewport();

    /**
     * Paints prepare
     **/
    virtual void paint_prepare();

	/**
	 * Paints the background layer of the trace with a QPainter
	 * @param p the QPainter to paint into.
	 * @param left the x-coordinate of the left edge of the signal
	 * @param right the x-coordinate of the right edge of the signal
	 **/
    virtual void paint_back(QPainter &p, int left, int right, QColor fore, QColor back);

	/**
	 * Paints the mid-layer of the trace with a QPainter
	 * @param p the QPainter to paint into.
	 * @param left the x-coordinate of the left edge of the signal
	 * @param right the x-coordinate of the right edge of the signal
	 **/
    virtual void paint_mid(QPainter &p, int left, int right, QColor fore, QColor back);

	/**
	 * Paints the foreground layer of the trace with a QPainter
	 * @param p the QPainter to paint into.
	 * @param left the x-coordinate of the left edge of the signal
	 * @param right the x-coordinate of the right edge of the signal
	 **/
    virtual void paint_fore(QPainter &p, int left, int right, QColor fore, QColor back);

	/**
     * Paints the trace label.
	 * @param p the QPainter to paint into.
	 * @param right the x-coordinate of the right edge of the header
	 * 	area.
     * @param point the mouse point.
	 */
    virtual void paint_label(QPainter &p, int right, const QPoint pt, QColor fore);

	/**
	 * Gets the y-offset of the axis.
	 */
	int get_y();

    /**
     * Determines if a point is in the header rect.
     * 1 - in color rect
     * 2 - in name rect
     * 3 - in posTrig rect
     * 4 - in higTrig rect
     * 5 - in negTrig rect
     * 6 - in lowTrig rect
     * 7 - in label rect
     * 0 - not
     * @param y the y-coordinate of the signal.
     * @param right the x-coordinate of the right edge of the header
     * 	area.
     * @param point the point to test.
     */
    int pt_in_rect(int y, int right,
        const QPoint &point);

    /**
     * Computes the outline rectangle of a label.
     * @param p the QPainter to lay out text with.
     * @param y the y-coordinate of the signal.
     * @param right the x-coordinate of the right edge of the header
     * 	area.
     * @return Returns the rectangle of the signal label.
     */
    QRectF get_rect(const char *s, int y, int right);

    virtual int rows_size();

    virtual QRect get_view_rect();

    virtual bool mouse_double_click(int right, const QPoint pt);

    virtual bool mouse_press(int right, const QPoint pt);

    virtual bool mouse_wheel(int right, const QPoint pt, const int shift);

protected:

	/**
	 * Gets the text colour.
	 * @remarks This colour is computed by comparing the lightness
	 * of the trace colour against a threshold to determine whether
	 * white or black would be more visible.
	 */
	QColor get_text_colour();

    /**
     * Paints optoins for different trace type.
     * @param p the QPainter to paint into.
     * @param right the x-coordinate of the right edge of the header
     * 	area.
     * @param point the mouse point.
     */
    virtual void paint_type_options(QPainter &p, int right, const QPoint pt, QColor fore);

private:

    /**
     * Computes an caches the size of the label text.
     */
    void compute_text_size(QPainter &p);

private slots:
	void on_text_changed(const QString &text);
	void on_colour_changed(const QColor &colour);
    virtual void resize();

signals:
	void visibility_changed();
	void text_changed();	
	void colour_changed();

protected:
	pv::view::View *_view;
    pv::view::Viewport *_viewport;

	QString _name;
	QColor _colour;
	int _v_offset;
    int _type;
    std::list<int> _index_list;
    int _sec_index;
    int _old_v_offset;
    int _totalHeight;
    int _typeWidth;

    QSizeF _text_size;
};

} // namespace view
} // namespace pv

#endif // DSVIEW_PV_VIEW_TRACE_H
