### Notes
The official implementation uses a different sequential algorithm to determine the snake length and geometry, that also takes into account for non-straight snakes. The algorithm is as follows:

* Find head
* Search for a `*` in a 3x3 area centered on the head
* Move current location to that piece
* Mark previous location as `visited` so that we do not consider it again
* Repeat from step 2

However, since the exercise text explicitly states that the snake "Lays down straight" I do not consider my solution (that relies on this assumption) to be wrong or incomplete.