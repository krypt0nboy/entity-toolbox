<?php

/**
 * Class EntityPropertyInfoModel
 */
class EntityPropertyInfoModel extends HookModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'structure' => array(
          'properties' => array(
            'type'    => 'array',
            'method'  => 'buildProperties',
            'model'   => 'entity_property_info_properties_property'
          ),
          'bundles'    => array(
            'type'    => 'array',
            'method'  => 'buildBundles',
            'model'   => 'entity_property_info_properties_property'
          ),
        )
      ),
      $args
    );
    parent::__construct($args);
  }
}