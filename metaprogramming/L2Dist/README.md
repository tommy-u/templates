Trivial example that you can write one function, say computing L2 dist between two 2D coordinates, that operates on two datatypes, float and double. The example is spiced up by restricting the types that the function can be called with to only float and double using the SFINAE: substitution failure is not an error pattern.