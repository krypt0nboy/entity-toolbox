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
            'default' => '%property_default_value_default%',
          ),
          'min length' => array(
            'type'     => 'string',
            'default'  => '%property_default_value_min_length%',
            'unset if' => '!is_numeric:c:',
          ),
          'max length' => array(
            'type'     => 'string',
            'default'  => '%property_default_value_max_length%',
            'unset if' => '!is_numeric:c:',
          ),
          'floor'      => array(
            'type'     => 'string',
            'default'  => '%property_default_value_floor%',
            'unset if' => '!is_numeric:c:',
          ),
          'ceil'       => array(
            'type'     => 'string',
            'default'  => '%property_default_value_ceil%',
            'unset if' => '!is_numeric:c:',
          ),
          'filter'     => array(
            'type'   => 'array',
            'method' => 'buildFilter',
          ),
          'forbid'     => array(
            'type'   => 'array',
            'method' => 'buildForbid',
          ),
        )
      ),
      $args
    );
    parent::__construct($args);
  }
}