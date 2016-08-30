<?php

/**
 * Returns an instance of a property type.
 *
 * @param array $type
 *   The property type.
 * @param array $args
 *   The args to get the instance.
 *
 * @return EntityToolboxPropertyBase
 */
function property_type_get_instance($type, array $args = array()) {
  $factory = new EntityToolboxPropertyFactory($type, $args);

  return $factory->getInstance();
}