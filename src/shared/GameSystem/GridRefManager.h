/**
 * MaNGOS is a full featured server for World of Warcraft, supporting
 * the following clients: 1.12.x, 2.4.3, 3.3.5a, 4.3.4a and 5.4.8
 *
 * Copyright (C) 2005-2025 MaNGOS <https://www.getmangos.eu>
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * World of Warcraft, and all World of Warcraft or Warcraft art, images,
 * and lore are copyrighted by Blizzard Entertainment, Inc.
 */

#ifndef _GRIDREFMANAGER
#define _GRIDREFMANAGER

#include "Utilities/LinkedReference/RefManager.h"

template<class OBJECT> class GridReference;

template<class OBJECT>
/**
 * @brief
 *
 */
class GridRefManager : public RefManager<GridRefManager<OBJECT>, OBJECT>
{
    public:

        /**
         * @brief
         *
         */
        typedef LinkedListHead::Iterator< GridReference<OBJECT> > iterator;

        /**
         * @brief
         *
         * @return GridReference<OBJECT>
         */
        GridReference<OBJECT>* getFirst()
        {
            return (GridReference<OBJECT>*)RefManager<GridRefManager<OBJECT>, OBJECT>::getFirst();
        }

        /**
         * @brief
         *
         * @return GridReference<OBJECT>
         */
        GridReference<OBJECT>* getLast()
        {
            return (GridReference<OBJECT>*)RefManager<GridRefManager<OBJECT>, OBJECT>::getLast();
        }

        /**
         * @brief
         *
         * @return iterator
         */
        iterator begin() { return iterator(getFirst()); }
        /**
         * @brief
         *
         * @return iterator
         */
        iterator end() { return iterator(nullptr); }
        /**
         * @brief
         *
         * @return iterator
         */
        iterator rbegin() { return iterator(getLast()); }
        /**
         * @brief
         *
         * @return iterator
         */
        iterator rend() { return iterator(nullptr); }
};
#endif
