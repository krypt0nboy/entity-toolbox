<?php

/**
 * @file
 *
 * This file contains functions to extract data from built info.
 */

/**
 * Extract the keys from entity info.
 *
 * @param array  $info
 *   The entity type info.
 * @param string $entity_type
 *   The entity type name.
 *
 * @return array
 */
function toolbox_info_extract_keys($info, $entity_type) {
  $keys       = array();
  $properties = &$info['properties'];
  foreach ($properties as $name => $property) {
    if (!empty($property['schemas_field_names']['base'])) {
      switch ($property['type']) {
        case 'id':
          $keys['id'] = $property['schemas_field_names']['base'];
          break;
        case 'bundle':
          $keys['bundle'] = $property['schemas_field_names']['base'];
          break;
        default :
          if (!empty($property['key'])) {
            $keys[$property['key']] = $property['schemas_field_names']['base'];
          }
          break;
      }
    }
  }

  return $keys;
}

/**
 * Extracts the schemas names for an entity type.
 *
 * @param array  $info
 *   The entity type toolbox info.
 * @param string $entity_type
 *   The entity type.
 *
 * @return string[]
 */
function toolbox_info_extract_schemas($info, $entity_type) {
  $buffer = array();
  foreach ($info['properties'] as $name => $property) {
    foreach ($property['schemas'] as $schema_type => $schema_name) {
      $buffer[$schema_name] = $schema_type;
    }
  }
  $schemas = array_unique($buffer);

  return $schemas;
}

/**
 * Extract the "base schema" fields.
 *
 * @param string $entity_type
 *   The entity type name.
 * @param string $schema_type
 *   The schema type, defaults "base".
 *
 * @return array
 */
function toolbox_info_extract_schema_fields($entity_type, $schema_type = 'base') {
  $schemas = &drupal_static(__FUNCTION__, array());
  if (!isset($schemas[$entity_type])) {
    $info       = entity_toolbox_entity_get_info($entity_type);
    $properties = $info[$entity_type]['properties'];
    foreach ($properties as $name => $property) {
      if (!empty($property['schemas_fields'][$schema_type])) {
        $schemas[$entity_type][$name] = $property['schemas_fields'][$schema_type];
      }
    }
  }

  return $schemas[$entity_type];
}

/**
 * Extracts the "base schema" field name of a property from entity_toolbox_entity_info (after build).
 *
 * @param string $entity_type
 *   The entity type.
 * @param string $name
 *   The property name.
 * @param string $schema_type
 *   The schema type, defaults "base".
 *
 * @return string
 */
function toolbox_property_extract_schema_field($entity_type, $name, $schema_type = 'base') {
  $info = entity_toolbox_entity_get_info($entity_type);

  return $info['properties'][$name]['schemas_field_names'][$schema_type];
}