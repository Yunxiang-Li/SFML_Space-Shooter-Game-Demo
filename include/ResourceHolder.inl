
/**
 * Load a resource to our resource map.
 * @tparam Resource Indicates the resource type
 * @tparam Identifier Indicates the identifier of the resource
 * @param id Indicates the identifier of the resource
 * @param filename Indicates the file path in string form
 */
template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
  // Create a unique_ptr to the resource.
  std::unique_ptr<Resource> resource(new Resource());
  // Try loading the resource from file path.
  if (!resource -> loadFromFile(filename))
    // If fail, throw a runtime error.
    throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

  // If loading successful, insert resource to the resource map.
  // We use std::move here to change resource from a lvalue to a rvalue.
  this -> insertResource(id, std::move(resource));
}

/**
 * Load a resource to our resource map with one more Parameter type(For sf::Shader).
 * @tparam Resource Indicates the resource type
 * @tparam Identifier Indicates the identifier of the resource
 * @tparam Parameter Indicates another Parameter type we need for loading the resource
 * @param id Indicates the identifier of the resource
 * @param filename Indicates the file path in string form
 * @param secondParam Indicates another Parameter type we need for loading the resource(sf::Shader::Type or const std::string&)
 */
template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& secondParam)
{
  // Create a unique_ptr to the resource.
  std::unique_ptr<Resource> resource(new Resource());
  // Try loading the resource from file path and one more parameter type (For sf::Shader).
  if (!resource -> loadFromFile(filename, secondParam))
    // If fail, throw a runtime error.
    throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

  // If loading successful, insert resource to the resource map.
  // We use std::move here to change resource from a lvalue to a rvalue.
  this -> insertResource(id, std::move(resource));
}

/**
 * Get the reference of a resource object according to its identifier.
 * @tparam Resource Indicates the resource type
 * @tparam Identifier Indicates the identifier of the resource
 * @param id Indicates the identifier of the resource
 * @return A reference to the relative resource object
 */
template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
  // Try to find the unique_ptr of the resource according to resource's identifier.
  auto found = mResourceMap.find(id);
  // Check if that resource exists or not.
  assert(found != mResourceMap.end());

  // Return the reference of that resource object.
  return *(found -> second);
}

/**
 * Same as normal get method but with two const keywords. The const at head means the return reference
 * of the resource object is const, the const at tail means no member variables will be changed in method's process.
 * @tparam Resource Indicates the resource type
 * @tparam Identifier Indicates the identifier of the resource
 * @param id Indicates the identifier of the resource
 * @return A const reference to the relative resource object
 */
template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
  // Try to find the unique_ptr of the resource according to resource's identifier.
  auto found = mResourceMap.find(id);
  // Check if that resource exists or not.
  assert(found != mResourceMap.end());
  // Return the reference of that resource object.
  return *(found -> second);
}

/**
 * Insert resource's identifier and unique_ptr as key value pair into the resource map.
 * @tparam Resource Indicates the resource type
 * @tparam Identifier Indicates the identifier of the resource
 * @param id Indicates the identifier of the resource
 * @param resource Indicates the unique_ptr of the resource
 */
template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insertResource(Identifier id, std::unique_ptr<Resource> resource)
{
  // Insert and check if the insertion process is success.
  auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
  assert(inserted.second);
}