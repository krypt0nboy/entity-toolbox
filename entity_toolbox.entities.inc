<?php

/**
 * @file
 *
 * This file contains functions required by \EntityToolboxEntity to interact with the system.
 *
 * @see \EntityToolboxEntity
 */

/**
 * Returns the default values used by \EntityToolboxEntityController to build a new entity.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return array
 *
 * @see \EntityToolboxEntityController::create()
 */
function entity_property_types_default($entity_type) {
  return entity_toolbox_controller($entity_type)->propertiesDefaultValues();
}

/**
 * Returns the default values used by \EntityToolboxEntityController to build a new entity.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $name
 *   The property name.
 *
 * @return mixed
 */
function entity_property_type_default($entity_type, $name) {
  return entity_toolbox_controller($entity_type)->propertyDefaultValue($name);
}

/**
 * Returns the default value for an entity property.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity.
 * @param string         $name
 *   The property name.
 *
 * @return mixed
 */
function entity_property_default($entity_type, $entity, $name) {
  return !empty($entity->$name) ? $entity->$name : entity_property_type_default($entity_type, $name);
}

/**
 * Default multi value setter callback for entity_toolbox entities.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity to set the values for.
 * @param string         $name
 *   The property name.
 * @param array          $values
 *   The values to set.
 */
function entity_toolbox_multi_value_property_set($entity_type, $entity, $name, $values) {
  entity_toolbox_controller($entity_type)->setMultiValueProperty($entity, $name, $values);
}

/**
 * Default multi value getter callback for entity_toolbox entities.
 *
 * @param string         $entity_type
 *   The entity type.
 * @param \EntityToolbox $entity
 *   The entity to get the values from.
 * @param string         $name
 *   The property name.
 *
 * @return array
 */
function entity_toolbox_multi_value_property_get($entity_type, $entity, $name) {
  return entity_toolbox_controller($entity_type)->getMultiValueProperty($entity, $name);
}

/**
 * Returns the bundles info of an entity_type.
 *
 * @param      $entity_type
 *   The entity_type for which to get the bundles.
 * @param null $type
 *   The bundle for which to get the info or NULL for all the bundles.
 *
 * @return array|mixed
 */
function entity_get_types($entity_type, $type = NULL) {
  return entity_toolbox_controller($entity_type)->types($type);
}

/**
 * Returns the entity type bundle names.
 *
 * @param string $entity_type
 *   The entity type.
 *
 * @return \string[]
 */
function entity_get_bundles($entity_type) {
  return entity_toolbox_controller($entity_type)->bundles();
}