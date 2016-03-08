/*
 ==============================================================================
 
 This file is part of the KIWI library.
 Copyright (c) 2014 Pierre Guillot & Eliott Paris.
 
 Permission is granted to use this software under the terms of either:
 a) the GPL v2 (or any later version)
 b) the Affero GPL v3
 
 Details of these licenses can be found at: www.gnu.org/licenses
 
 KIWI is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 
 ------------------------------------------------------------------------------
 
 To release a closed-source product which uses KIWI, contact : guillotpierre6@gmail.com
 
 ==============================================================================
 */

#ifndef KIWI_PATH_H_INCLUDED
#define KIWI_PATH_H_INCLUDED

#include <KiwiGraphics/KiwiPoint.hpp>
#include <KiwiGraphics/KiwiAffineMatrix.hpp>
#include <assert.h>


namespace kiwi
{
    namespace graphics
    {
        // ================================================================================ //
        //                                      PATH                                        //
        // ================================================================================ //
        
        //!@brief The path holds a set of points.
        //!@details The path is used to represent a set of curves and shapes. It can be discontinuous and closed.
        //!@todo Check if constructors with shapes are needed
        //!@todo Check if withdrawn functions are needed (addArc, addRectangle, addElipse, addPieChart, addArc, overlaps)
        //!@todo Check if bounds are needed and how they can be implemented (dizcretisation, recompute at every change)
        class Path
        {
        public:
            //!@brief Default constructor
            //!@details Initializes a path positioned at the origin
            inline Path() noexcept {addNode(Node(Point(), Move));};
            
            //!@brief Copy constructor
            //!@details Copies all the nodes of a path
            inline Path(Path const& path) noexcept : m_nodes(path.m_nodes) {}
            
            //!@brief Move constructor
            //!@details Moves the nodes to the new constructed path
            inline Path(Path&& path) noexcept : m_nodes(std::forward<std::vector<Node>>(path.m_nodes)){};
            
            //!@brief Position constructor
            //!@details Initializes a constructor at a certain position
            inline Path(Point const& position) noexcept {addNode(Node(position, Move));}
            
            //!@brief Assignment operator
            //!@details Clear all nodes and copies all nodes from other
            inline Path& operator=(Path const& other) noexcept;
            
            //!@brief Move assignment operator
            //!@details Moves the nodes from other
            inline Path& operator=(Path&& other) noexcept;
            
            //@brief Destructor
            ~Path() noexcept = default;
            
            //!@brief Gets the number of nodes
            inline ulong size() const noexcept {return static_cast<ulong>(m_nodes.size());}
            
            //!@brief Return true if the path is empty
            inline bool empty() const noexcept {return m_nodes.size() <= 1;}
            
            //!@brief Removes all node
            //!@details After clear, the path continues drawing from origin
            inline void clear() noexcept;
            
            //!@brief Applies an affine transform to the path
            //!@details AffineTransform is applied to all nodes
            void transform(AffineMatrix const& matrix) noexcept;
            
            //!@brief Gets a affine transformed path
            //!@details Retrieves a copy, doesn't apply changes to path
            Path transformed(AffineMatrix const& matrix) const noexcept;
            
            //!@brief Moves drawing cursor to the position
            //!@details Doesn't actually move the nodes, sets the next drawing position instead. Paths can be discontinuous.
            void moveTo(Point const& position) noexcept;

            //!@brief Adds a line to the current path
            //!@param line_hedge Draws a line from cursor to line_hedge
            void lineTo(Point const& line_hedge) noexcept;
            
            //!@brief Adds a sets of line
            //!@param il Contains the hedges position of the added lines
            void linesTo(std::initializer_list<Point> il) noexcept;
            
            //!@brief Adds a quadradic bezier curve
            void quadraticTo(Point const& control, Point const& end) noexcept;
            
            //!@brief Adds a set of quadratic bezier curves
            //!@param il Contains the control positions for every quadradic curve
            void quadraticsTo(std::initializer_list<std::array<Point, 2>> il) noexcept;
            
            //!@brief Adds a cubic curve to the path
            void cubicTo(Point const& control1, Point const& control2, Point const& end) noexcept;
            
            //!@brief Adds a set of cubic bezier curves
            //!@param il Contains the control positions for every cubic curve
            void cubicsTo(std::initializer_list<std::array<Point, 3>> il) noexcept;
            
            //!@brief Adds rectangle to the path
            //!@param top_left The top_left corner position of the added rectangle
            //!@param width Horizontal width of the rectangle
            //!@param height Horizontal height of the the rectangle
            void addRectangle(Point const& top_left, const double width, const double height) noexcept;
            
            //!@brief Add an ellipse to the path
            //!@param center Center of the ellipse
            //!@param radius_x Horizontal radius
            //!@param radius_y Vertical radius
            void addEllipse(Point const& center, const double radius_x, const double radius_y) noexcept;
            
            //!@brief Appends a path
            void addPath(Path const& path) noexcept;
            
            //!@brief Closes the final hedge of the path
            //!@details If the path is discontinuous, only the final part of the path is closed
            void close() noexcept;
            
        private:
            //!@internal
            enum Mode
            {
                Close       = 0,
                Move        = 1,
                Linear      = 2,
                Quadratic   = 3,
                Cubic       = 4
            };
            
            //!@internal
            class Node
            {
            public:
                constexpr inline Node(Point const& pos, const Mode mode) noexcept : m_pos(pos), m_mode(mode){};
                
                constexpr inline Node(Node const& other) noexcept : m_pos(other.m_pos), m_mode(other.m_mode){};
                Node& operator=(Node const& other) noexcept;
                
                inline ~Node() noexcept = default;
                
                constexpr inline Point getPos() const noexcept{return m_pos;}
                constexpr inline Mode getMode() const noexcept{return m_mode;}
                
                inline void setPos(const Point pos) noexcept {m_pos = pos;};
                
                void transform(AffineMatrix const& matrix) noexcept {matrix.applyTo(m_pos);}
                
                Node() = delete;
                
            private:
                Point m_pos;
                Mode  m_mode;
            };
            
            //!@internal
            bool haveSamePos(Node const& node_l, Node const& node_r) const noexcept;
            
            std::vector<Node> m_nodes;
            
            //@!internal
            Node lastMoveNode() const noexcept;
            
            //!@internal
            inline void addNode(Node const& node) noexcept{m_nodes.push_back(node);
            }
        };
    }
}

#endif // KIWI_PATH_H_INCLUDED
