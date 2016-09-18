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
  $args += array('property_type' => $type);
  $factory = new EntityToolboxPropertyFactory($args);

  return $factory->getInstance();
}