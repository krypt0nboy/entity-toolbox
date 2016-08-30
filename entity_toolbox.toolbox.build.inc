<?php

/**
 * Return build info for entity_toolbox_info().
 *
 * @param string $type
 *   The entity type.
 * @param array  $info
 *   The retrieved raw entity_toolbox_info.
 *
 * @return array
 */
function entity_toolbox_info_build($type, $info) {
  $class = $info['fieldable'] ? 'EntityToolboxInfoBuilderFieldable' : 'EntityToolboxInfoBuilderNotFieldable';
  /** @var EntityToolboxInfoBuilder $builder */
  $args    = array(
    'entity_type' => $type,
    'raw_data'    => $info
  );
  $builder = new $class($args);
  $build   = $builder->build();

  return $build;
}

/**
 * Return the toolbox_info for an entity not managed by entity_toolbox.
 *
 * @param string $reference_type
 *   The reference entity_type.
 *
 * @return array
 */
function entity_toolbox_info_reverse_build($reference_type) {

}

/**
 * Return build info for an entity_toolbox property.
 *
 * @param string $type
 *   The entity type.
 * @param string $name
 *   The property name.
 * @param array  $info
 *   The retrieved raw entity_toolbox_info.
 *
 * @return array
 */
function entity_toolbox_property_build($type, $name, $info) {

}