<?php

/**
 * Class EntityToolboxInfoPropertyCallbacksModel
 */
class EntityToolboxInfoPropertyCallbacksModel extends EntityToolboxInfoRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key'  => 'callbacks',
        'structure' => array(
          'getter'       => array(
            'type'     => 'string',
            'method'   => 'buildGetterCallback',
            'default'  => '%property_default_callbacks_getter%',
            'unset if' => 'is_template_value:c:',
          ),
          'setter'       => array(
            'type'     => 'string',
            'method'   => 'buildSetterCallback',
            'default'  => '%property_default_callbacks_setter%',
            'unset if' => 'is_template_value:c:',
          ),
          'validation'   => array(
            'type'     => 'string',
            'default'  => '%property_default_callbacks_validation%',
            'unset if' => 'is_template_value:c:',
          ),
          'permission'   => array(
            'type'     => 'string',
            'default'  => '%property_default_callbacks_permission%',
            'unset if' => 'is_template_value:c:',
          ),
          'default'      => array(
            'type'     => 'string',
            'default'  => '%property_default_callbacks_default%',
            'unset if' => 'is_template_value:c:',
          ),
          'options list' => array(
            'type'     => 'string',
            'default'  => '%property_default_callbacks_options_list%',
            'unset if' => 'is_template_value:c:',
          ),
        )
      ),
      $args
    );
    parent::__construct($args);
  }
}