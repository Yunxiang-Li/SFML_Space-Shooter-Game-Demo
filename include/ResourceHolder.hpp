#ifndef RESOURCEHOLDER_HPP
#define RESOURCEHOLDER_HPP

// Include C++ standard headers.
#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

/**
 * Template for ResourceHolder class which will hold all resource we use in this game.
 * @tparam Resource Indicates the type of resource.
 * @tparam Identifier Indicates the identifier of the resource(For instance, sf::Texture::ID) helps us find the mapping
 * resource
 */
template <typename Resource, typename Identifier>
class ResourceHolder
{
 public:
  // Load a resource to our resource map.
  void						load(Identifier id, const std::string& filename);
  // Load a resource to our resource map with one more Parameter type(For sf::Shader).
  template <typename Parameter>
  void						load(Identifier id, const std::string& filename, const Parameter& secondParam);
  // Get the reference of a resource object according to its identifier.
  Resource&					get(Identifier id);
  // Get the const reference of a resource object according to its identifier(no members will be changed in the process).
  const Resource&			get(Identifier id) const;

 private:
  // Insert resource's identifier and unique_ptr as key value pair into the resource map.
  void						insertResource(Identifier id, std::unique_ptr<Resource> resource);

 private:
  // A ordered map which takes resource's identifier as key and resource's unique pointer as value.
  std::map<Identifier, std::unique_ptr<Resource>>	mResourceMap;
};

#include "ResourceHolder.inl"
#endif // RESOURCEHOLDER_HPP