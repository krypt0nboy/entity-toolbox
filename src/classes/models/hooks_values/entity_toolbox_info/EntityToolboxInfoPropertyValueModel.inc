<?php

/**
 * Class EntityToolboxInfoPropertyValueModel
 */
class EntityToolboxInfoPropertyValueModel extends EntityToolboxInfoRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key'  => 'value',
        'structure' => array(
          'default'    => array(
            'type'    => 'string',
            'method'  => '',
            'default' => '%property_default_value_default%',
            'model'   => ''
          ),
          'min length' => array(
            'type'    => 'string',
            'method'  => '',
            'default' => '%property_default_value_min_length%',
            'model'   => ''
          ),
          'max length' => array(
            'type'    => 'string',
            'method'  => '',
            'default' => '%property_default_value_max_length%',
            'model'   => ''
          ),
          'floor'      => array(
            'type'    => 'string',
            'method'  => '',
            'default' => '%property_default_value_floor%',
            'model'   => ''
          ),
          'ceil'       => array(
            'type'    => 'string',
            'method'  => '',
            'default' => '%property_default_value_ceil%',
            'model'   => ''
          ),
          'filter'     => array(
            'type'    => 'array',
            'method'  => 'buildFilter',
            'default' => '',
            'model'   => ''
          ),
          'forbid'     => array(
            'type'    => 'array',
            'method'  => 'buildForbid',
            'default' => '',
            'model'   => ''
          ),
        )
      ),
      $args
    );
    parent::__construct($args);
  }
}