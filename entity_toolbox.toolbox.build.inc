<?php

/**
 * Return build info for entity_toolbox_info().
 *
 * @param string $type
 * @param array  $info
 *
 * @return array
 */
function entity_toolbox_info_build($type, $info) {
  $builder = $info['fieldable'] ? new EntityToolboxInfoBuilderFieldable($type, $info) : new EntityToolboxInfoBuilderNotFieldable($type, $info);

  return $builder->build();
}

/**
 * Return build info for an entity_toolbox property.
 *
 * @param string $type
 * @param string $name
 * @param array  $info
 *
 * @return array
 */
function entity_toolbox_property_build($type, $name, $info) {

}