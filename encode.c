 # i n c l u d e   " e n c o d e . h "  
  
 # d e f i n e   C H S E T _ S I Z E   2 5 5  
  
 i n t   m a i n ( i n t   a r g c ,   c h a r   * a r g v [ ] )   {  
 	 t r e e   * h e a d   =   m a k e _ t r e e ( 1 ,   E O F ) ;  
  
 	 F I L E   * f i l e   =   f o p e n ( * ( a r g v   +   1 ) ,   " r " ) ;  
 	 i f ( f i l e   = =   N U L L )   {  
 	 	 p r i n t f ( " E r r o r :   % s \ n " ,   s t r e r r o r ( e r r n o ) ) ;  
 	 	 r e t u r n   1 ;  
 	 }  
 	 i n t   w e i g h t s [ C H S E T _ S I Z E ] ;  
 	 f o r ( i n t   i = 0 ;   i < C H S E T _ S I Z E ;   i + + )   {  
 	 	 w e i g h t s [ i ]   =   0 ;  
 	 }  
 	 i n t   c ;   / / t h e   p r o b l e m   i s   t h a t   i ' m   u s i n g   e o f   a s   a   h e a d  
 	 w h i l e ( ( c = f g e t c ( f i l e ) )   ! =   E O F )   {  
 	 	 w e i g h t s [ c ] + + ;  
 	 }  
 	 f o r ( i n t   i = 0 ;   i < C H S E T _ S I Z E ;   i + + )   {  
 	 	 i f ( w e i g h t s [ i ] )   {  
 	 	 	 h e a d   =   i n s e r t ( m a k e _ t r e e ( w e i g h t s [ i ] ,   i ) ,   h e a d ) ;  
 	 	 }  
 	 }  
 	 h e a d = h u f _ e n c o d e ( h e a d ) ;  
 	 / /   c h a r   c o d e [ 1 0 0 ] ;  
 	 / /   p r i n t _ i n ( h e a d ,   c o d e ,   0 ) ;  
 	 p r i n t _ p r e ( h e a d ) ;  
  
 	 r e w i n d ( f i l e ) ;  
  
 	 p r i n t _ e n c o d e d ( f i l e ,   h e a d ) ;  
  
 	 / /   i n t   t o t a l   =   0 ;  
 	 / /   c h a r *   s t r i n g ;  
 	 / /   w h i l e ( ( c = f g e t c ( f i l e ) )   ! =   E O F )   {  
 	 / /   	 s t r i n g   =   s e a r c h ( h e a d ,   c ) ;  
 	 / /   	 t o t a l   + =   s t r l e n ( s t r i n g ) ;  
 	 / /   	 f r e e ( s t r i n g ) ;  
 	 / /   }  
 	 / /   s t r i n g   =   s e a r c h ( h e a d ,   c ) ;  
 	 / /   t o t a l   + =   s t r l e n ( s t r i n g ) ;  
 	 / /   f r e e ( s t r i n g ) ;  
  
 	 / /   p r i n t f ( " T o t a l   s i z e   w i t h o u t   e n c o d i n g :   % d   b y t e s \ n " ,   h e a d - > w e i g h t * s i z e o f ( c h a r ) ) ;  
 	 / /   p r i n t f ( " T o t a l   s i z e   w i t h   e n c o d i n g :   % d   b y t e s \ n " ,   t o t a l / 8 ) ;  
  
  
  
 	 f c l o s e ( f i l e ) ;  
 	 c l e a n ( h e a d ) ;  
 }  
  
 v o i d   p r i n t _ p r e ( t r e e   * h e a d )   {  
 	 i f ( h e a d - > l e f t   | |   h e a d - > r i g h t )   {  
 	 	 p u t c h a r ( ' 0 ' ) ;  
 	 	 p u t c h a r ( '   ' ) ;  
 	 }  
 	 e l s e   i f ( h e a d   = =   N U L L )   {  
 	 	 p r i n t f ( " U n e x p e c t e d   l e a f . \ n " ) ;  
 	 	 r e t u r n ;  
 	 }  
 	 e l s e   {  
 	 	 p u t c h a r ( ' 1 ' ) ;  
 	 	 p u t c h a r ( '   ' ) ;  
 	 	 p r i n t _ b i n a r y ( h e a d - > c ) ;  
 	 	 p u t c h a r ( '   ' ) ;  
 	 	 r e t u r n ;  
 	 }  
 	 p r i n t _ p r e ( h e a d - > l e f t ) ;  
 	 p r i n t _ p r e ( h e a d - > r i g h t ) ;  
 }  
  
 v o i d   p r i n t _ b i n a r y ( i n t   c )   {  
 	 f o r ( i n t   i = C H A R _ B I T - 1 ;   i > = 0 ;   i - - )   {  
 	 	 p u t c h a r ( ( c   &   ( 1 < < i ) ) ? ' 1 ' : ' 0 ' ) ;  
 	 }  
 }  
  
 v o i d   p r i n t _ e n c o d e d ( F I L E   * f i l e ,   t r e e   * h e a d )   {  
 	 c h a r   * c h a r a c t e r ;  
 	 i n t   c ;  
 	 i n t   i n d e x   =   0 ;  
 	 i n t   v a l u e   =   0 ;  
 	 w h i l e ( ( c = f g e t c ( f i l e ) )   ! =   E O F )   {  
 	 	 c h a r a c t e r   =   s e a r c h ( h e a d ,   c ) ;  
 	 	 f o r (   ;   * c h a r a c t e r ;   c h a r a c t e r + + )   {  
 	 	 	 v a l u e   =   p r i n t _ b i t s ( i n d e x ,   * c h a r a c t e r   -   ' 0 ' ,   v a l u e ) ;  
 	 	 	 i f ( i n d e x   = =   C H A R _ B I T - 1 )   {  
 	 	 	 	 i n d e x   =   0 ;  
 	 	 	 }  
 	 	 	 e l s e   {  
 	 	 	 	 i n d e x + + ;  
 	 	 	 }  
 	 	 }  
 	 }  
 	 w h i l e ( i n d e x   >   0   & &   i n d e x   <   C H A R _ B I T )   {  
 	         p r i n t _ b i t s ( i n d e x + + ,   0 ,   v a l u e ) ;  
 	 }  
 }  
  
 i n t   p r i n t _ b i t s ( i n t   i n d e x ,   i n t   b i t ,   i n t   v a l u e )   {  
 	 v a l u e   =   v a l u e   |   b i t < < ( C H A R _ B I T   -   i n d e x   -   1 ) ;  
 	 i f ( i n d e x   = =   7 )   {  
 	 	 p r i n t f ( " % c " ,   v a l u e ) ;  
 	 	 r e t u r n   0 ;  
 	 }  
 	 e l s e   {  
 	 	 r e t u r n   v a l u e ;  
 	 }  
 }  
  
 / *   S e a r c h   t h e   h u f f m a n   t r e e   f o r   t h e   s y m b o l ,   r e t u r n i n g   i t s   b i t s t r i n g   i f   f o u n d   o r   a n   e m p t y   s t r i n g   i f   n o t   f o u n d .   B e   s u r e   t o   f r e e   a f t e r   u s e .   * /  
 c h a r *   s e a r c h ( t r e e   * h e a d ,   i n t   s y m b o l )   {  
 	 c h a r   * c o d e   =   m a l l o c ( 1 0 0 ) ;  
 	 * c o d e   =   ' \ 0 ' ;  
 	 i n t   i n d e x   =   0 ;  
 	 i n d e x   =   r _ s e a r c h ( h e a d ,   s y m b o l ,   & c o d e ,   0 ) ;  
 	 * ( c o d e   +   i n d e x )   =   ' \ 0 ' ;  
 	 r e t u r n   c o d e ;  
 }  
  
 i n t   r _ s e a r c h ( t r e e   * h e a d ,   i n t   s y m b o l ,   c h a r * *   c o d e ,   i n t   i n d e x )   {  
 	 i f ( h e a d - > c   = =   s y m b o l )   {  
 	 	 r e t u r n   i n d e x ;  
 	 }  
 	 e l s e   i f ( ! h e a d - > l e f t   & &   ! h e a d - > r i g h t )   {  
 	 	 r e t u r n   0 ;  
 	 }  
 	 e l s e   i f ( h e a d - > l e f t )   {  
 	 	 i n t   i   =   r _ s e a r c h ( h e a d - > l e f t ,   s y m b o l ,   c o d e ,   i n d e x + 1 ) ;  
 	 	 i f ( i )   {  
 	 	 	 * ( * c o d e   +   i n d e x )   =   ' 0 ' ;  
 	 	 	 r e t u r n   i ;  
 	 	 }  
 	 }  
 	 i f ( h e a d - > r i g h t )   {  
 	 	 i n t   i   =   r _ s e a r c h ( h e a d - > r i g h t ,   s y m b o l ,   c o d e ,   i n d e x + 1 ) ;  
 	 	 i f ( i )   {  
 	 	 	 * ( * c o d e   +   i n d e x )   =   ' 1 ' ;  
 	 	 	 r e t u r n   i ;  
 	 	 }  
 	 }  
 	 r e t u r n   0 ;  
 }  
  
 / *   E n c o d e s   t h e   l i s t   o f   s i n g l e t o n s   i n t o   a   h u f f m a n   t r e e   a n d   r e t u r n s   t h e   h e a d .   * /  
 t r e e *   h u f _ e n c o d e ( t r e e   * h e a d )   {  
 	 w h i l e ( ( h e a d = h u f f m a n _ s t e p ( h e a d ) ) - > n e x t ) { }  
 	 r e t u r n   h e a d ;  
 }  
  
 / *   R e c u r s i v e l y   f r e e s   t h e   t r e e - l i s t   w h o s   f i r s t   n o d e   i s   p o i n t e d   t o   b y   h e a d .   * /  
 v o i d   c l e a n ( t r e e   * h e a d )   {  
 	 i f ( h e a d - > l e f t   ! =   N U L L )   {  
 	 	 c l e a n ( h e a d - > l e f t ) ;  
 	 }  
 	 i f ( h e a d - > r i g h t   ! =   N U L L )   {  
 	 	 c l e a n ( h e a d - > r i g h t ) ;  
 	 }  
 	 i f ( h e a d - > n e x t   ! =   N U L L )   {  
 	 	 c l e a n ( h e a d - > n e x t ) ;  
 	 }  
 	 f r e e ( h e a d ) ;  
 }  
  
 v o i d   p r i n t _ i n ( t r e e   * h e a d ,   c h a r   c o d e [ ] ,   i n t   i n d e x )   {  
 	 i f ( h e a d - > l e f t )   {  
 	 	 c o d e [ i n d e x ]   =   ' 0 ' ;  
 	 	 p r i n t _ i n ( h e a d - > l e f t ,   c o d e ,   i n d e x + 1 ) ;  
 	 }  
 	 i f ( h e a d - > r i g h t )   {  
 	 	 c o d e [ i n d e x ]   =   ' 1 ' ;  
 	 	 p r i n t _ i n ( h e a d - > r i g h t ,   c o d e ,   i n d e x + 1 ) ;  
 	 }  
 	 i f ( ! h e a d - > r i g h t   & &   ! h e a d - > l e f t )   {  
 	 	 c o d e [ i n d e x ] = ' \ 0 ' ;  
 	 	 i f ( h e a d - > c   > =   0   & &   h e a d - > c   <   1 2 8 )   {  
 	 	 	 p r i n t f ( " % c :   % s \ n " ,   h e a d - > c ,   c o d e ) ;  
 	 	 }  
 	 	 e l s e   {  
 	 	 	 p r i n t f ( " % d :   % s \ n " ,   h e a d - > c ,   c o d e ) ;  
 	 	 }  
 	 }  
 }  
  
 / *   P e r f o r m s   o n e   s t e p   o f   t h e   h u f f m a n   t r e e   c r e a t i o n   o n   t h e   s o r t e d   l i s t   w h o s e   f i r s t   n o d e   i s   p o i n t e d   t o   b y   h e a d .   * /  
 t r e e *   h u f f m a n _ s t e p ( t r e e   * h e a d )   {  
 	 t r e e   * n e w _ n o d e   =   h e a d ;  
 	 t r e e   * o l d _ h e a d   =   h e a d ;  
 	 i f ( h e a d - > n e x t - > n e x t )   {  
 	 	 n e w _ n o d e = m a k e _ t r e e ( h e a d - > w e i g h t   +   h e a d - > n e x t - > w e i g h t ,   0 ) ;  
 	 	 n e w _ n o d e - > l e f t   =   h e a d ;  
 	 	 n e w _ n o d e - > r i g h t   =   h e a d - > n e x t ;  
 	 	 h e a d   =   i n s e r t ( n e w _ n o d e ,   h e a d - > n e x t - > n e x t ) ;  
 	 }  
 	 e l s e   i f ( h e a d - > n e x t )   {   / / o n l y   2   e l e m e n t s  
 	 	 n e w _ n o d e   =   m a k e _ t r e e ( h e a d - > w e i g h t   +   h e a d - > n e x t - > w e i g h t ,   0 ) ;  
 	 	 n e w _ n o d e - > l e f t   =   h e a d ;  
 	 	 n e w _ n o d e - > r i g h t   =   h e a d - > n e x t ;  
 	 	 h e a d   =   n e w _ n o d e ;  
 	 }  
 	 / /   i f ( h e a d   ! =   o l d _ h e a d   | |   ! o l d _ h e a d - > n e x t   | |   ! o l d _ h e a d - > n e x t - > n e x t )   {  
 	 / /   	 r e s u l t   =   n e w _ n o d e ;  
 	 / /   }  
 	 / /   e l s e   {  
 	 / /   	 r e s u l t   =   h e a d - > n e x t - > n e x t ;  
 	 / /   }  
 	 i f ( o l d _ h e a d - > n e x t )   {  
 	 	 o l d _ h e a d - > n e x t - > n e x t   =   N U L L ;   / / g o t t a   a v o i d   i n f i n i t e   l o o p s  
 	 }  
 	 o l d _ h e a d - > n e x t   =   N U L L ;  
 	 / /   p r i n t f ( " N e w   O r d e r i n g :   " ) ;  
 	 / /   p r i n t _ t r e e ( h e a d ) ;  
 	 / /   p r i n t f ( " \ n " ) ;  
 	 / /   p r i n t f ( " N e w   h e a d :   % d ,   % d \ n " ,   h e a d - > c ,   h e a d - > w e i g h t ) ;  
 	 r e t u r n   h e a d ;  
 }  
  
 v o i d   p r i n t _ t r e e ( t r e e *   h e a d )   {  
 	 w h i l e ( h e a d   ! =   N U L L )   {  
 	 	 / /   i f ( h e a d - > c   > =   0 )   {  
 	 	 / /   	 p r i n t f ( " % c :   % d , " ,   h e a d - > c ,   h e a d - > w e i g h t ) ;  
 	 	 / /   }  
 	 	 / /   e l s e   {  
 	 	 p r i n t f ( " ( % d ,   % d ) , " ,   h e a d - > c ,   h e a d - > w e i g h t ) ;  
 	 	 / /   }  
 	 	 h e a d   =   h e a d - > n e x t ;  
 	 }  
 	 p r i n t f ( " \ n " ) ;  
 }  
  
 / *   I n t i a l i z e   a   s i n g l e t o n   n o d e   f o r   s p e c i f i e d   c h a r a c t e r   a n d   w e i g h t   ( f r e q u e n c y ) .   * /  
 t r e e *   m a k e _ t r e e ( i n t   w e i g h t ,   i n t   c )   {  
 	 t r e e   * r e s u l t   =   m a l l o c ( s i z e o f ( t r e e ) ) ;  
 	 i f ( r e s u l t   = =   N U L L )   {  
 	 	 f p r i n t f ( s t d e r r ,   " E r r o r :   i n a d e q u a t e   h e a p   s p a c e . \ n " ) ;  
 	 	 e x i t ( 1 ) ;  
 	 }  
 	 r e s u l t - > c   =   c ;  
 	 r e s u l t - > w e i g h t   =   w e i g h t ;  
 	 r e s u l t - > n e x t   =   N U L L ;  
 	 r e s u l t - > l e f t   =   N U L L ;  
 	 r e s u l t - > r i g h t   =   N U L L ;  
 	 r e t u r n   r e s u l t ;  
 }  
  
 / *   I n s e r t   t h e   n e w _ n o d e   i n t o   t h e   t r e e   a n d   r e t u r n   t h e   n e w   h e a d .   * /  
 t r e e *   i n s e r t ( t r e e   * n e w _ n o d e ,   t r e e   * h e a d )   {  
 	 / /   p r i n t f ( " B e f o r e   i n s e r t i n g   e l e m e n t   ( % d ,   % d )   " ,   n e w _ n o d e - > c ,   n e w _ n o d e - > w e i g h t ) ;  
 	 p r i n t _ t r e e ( h e a d ) ;  
 	 / /   i n t   i = 0 ;  
 	 t r e e   * r e s u l t   =   h e a d ;  
 	 i f ( n e w _ n o d e - > w e i g h t   < =   h e a d - > w e i g h t )   {  
 	 	 r e s u l t   =   n e w _ n o d e ;  
 	 	 n e w _ n o d e - > n e x t   =   h e a d ;  
 	 }  
 	 e l s e   {  
 	 	 w h i l e ( h e a d - > n e x t   & &   h e a d - > n e x t - > w e i g h t   <   n e w _ n o d e - > w e i g h t )   {  
 	 	 	 h e a d   =   h e a d - > n e x t ;  
 	 	 	 / /   i + + ;  
 	 	 }  
 	 	 t r e e   * t m p   =   h e a d - > n e x t ;  
 	 	 h e a d - > n e x t   =   n e w _ n o d e ;  
 	 	 n e w _ n o d e - > n e x t   =   t m p ;  
 	 }  
  
 	 r e t u r n   r e s u l t ;  
 }  
