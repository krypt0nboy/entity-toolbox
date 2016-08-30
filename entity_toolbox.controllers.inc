<?php

/**
 * @file
 *
 * This file contains the functions required by \EntityToolboxEntityController to interact with drupal.
 *
 * @see \EntityToolboxEntityController
 */

/**
 * Returns a list of properties to be inherited by children entities.
 *
 * @param $entity_type
 *   The entity type.
 *
 * @return \string[]
 */
function entity_get_inheritable_properties($entity_type) {
  return entity_toolbox_controller($entity_type)->inheritableProperties();
}

/**
 * Returns a list of properties inherited from parent entities.
 *
 * @param $entity_type
 *   The entity type.
 *
 * @return \array[]
 */
function entity_get_inherited_properties($entity_type) {
  return entity_toolbox_controller($entity_type)->inheritedProperties();
}

/**
 * Returns a list of fields inheritable from parent entities.
 *
 * @param $entity_type
 *   The entity type.
 * @param $bundle
 *   The entity bundle.
 *
 * @return array
 */
function entity_get_inheritable_fields($entity_type, $bundle) {
  /** @var \EntityToolboxControllerFieldable $controller */
  $controller = entity_toolbox_controller($entity_type);

  return $controller->inheritableFields($bundle);
}

/**
 * Returns a list of fields inherited from parent entities.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $bundle
 *   The entity bundle.
 *
 * @return array
 */
function entity_get_inherited_fields($entity_type, $bundle) {
  /** @var \EntityToolboxControllerFieldable $controller */
  $controller = entity_toolbox_controller($entity_type);

  return $controller->inheritedFields($bundle);
}

/**
 * Returns a boolean indicating if the property is multi value or not.
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $name
 *   The property name.
 *
 * @return bool
 */
function is_property_multi_value($entity_type, $name) {
  return entity_toolbox_controller($entity_type)->isPropertyMultiValue($name);
}