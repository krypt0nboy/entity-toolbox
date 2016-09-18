<?php

/**
 * Class EntityWeightProperty
 */
class EntityWeightProperty extends WeightProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'default_type'           => 'entity_weight',
      'default_name'           => 'weight',
      'default_description'    => 'The weight of this %toolbox_info_bundle_of% type.',
      'default_schemas_fields' => array(
        'base'     => array(
          'description' => 'The weight of this %toolbox_info_bundle_of% type in relation to others.',
        ),
        'revision' => array(
          'description' => 'The weight of this %toolbox_info_bundle_of% type in relation to others.',
        ),
      ),
      'default_value'          => array(
        'default' => 0
      )
    ), $args);
    parent::__construct($args);
  }
}